using ExpectationLib;

namespace Citrix.CloudServices.Messaging.UnitTests.Expectation
{
    [TestFixture]
    public class ExpectationTests
    {
        [Test]

        public void Test_Sender()
        {
            const string senderId = "senderId";
            var sender = new Party(senderId);
            Assert.That(sender.Id, Is.EqualTo(senderId));
        }

        [Test]
        public void Test_Receiver()
        {
            const string receiverId = "receiverId";
            var receiver = new Party(receiverId);
            Assert.That(receiver.Id, Is.EqualTo(receiverId));
        }

        [Test]
        public void Test_CustomStimulus()
        {
            var sender = new Party("receiver1");
            var receiver = new Party("receiver2");

            var stimulus = new ContactsStimulus(sender, receiver);
            Assert.That(stimulus.Sender, Is.EqualTo(sender));
            Assert.That(stimulus.Receiver, Is.EqualTo(receiver));
            Assert.That(stimulus.Id, Is.EqualTo(ContactsStimulus.CreateId(sender, receiver)));
        }

        
        [Test]
        public void Test_Overseer()
        {
            var observer = new Observer();
            var sender = new Party("receiver1");
            var receiver = new Party("receiver2");            
            var sender2 = new Party("receiver2");
            var receiver2 = new Party("receiver2");
            var stimulus1 = new ContactsStimulus(sender, receiver);
            var stimulus2 = new ContactsStimulus(sender2, receiver2);
            var response = new ContactResponse("responseA", receiver);
            var response2 = new ContactResponse("responseB", receiver);

            Assert.That(observer.Observations, Is.Empty);
            
            var observation = observer.Observe(stimulus1, response);
            
            Assert.That(observer.Observations.Count, Is.EqualTo(1));
            Assert.That(observation.Response, Is.EqualTo(response));
            Assert.That(observation.Stimulus, Is.EqualTo(stimulus1));

            var observation2 = observer.Observe(stimulus2, response2);
            Assert.That(observer.Observations.Count, Is.EqualTo(2));
            Assert.That(observation2.Response, Is.EqualTo(response2));
            Assert.That(observation2.Stimulus, Is.EqualTo(stimulus2));
        }

        [Test]
        public void Test_Expectation()
        {
            var observer = new Observer();
            var sender = new Party("Stuart");
            var receiver = new Party("Jenny");

            // create a certain kind of stimulus Mechanosensory (Contact) from sender -> receiver
            var stimulus = new ContactsStimulus(sender, receiver);

            var expectedResponse = new ContactResponse("aResponse", receiver);

            // Create an expectation
            var myExpectation = new StimuliProducesResponseExpectation(stimulus, expectedResponse);
            
            // perform a stimulus .. sender contacts receiver and a contact response is produced
            
            // make sure the observer observes it
            observer.Observe(stimulus, expectedResponse);

            // Ensure the expectation is met by observations

            Assert.That(myExpectation.Stimuli, Is.EqualTo(stimulus));
            Assert.That(myExpectation.Stimuli.Sender, Is.EqualTo(stimulus.Sender));
            Assert.That(myExpectation.Stimuli.Receiver, Is.EqualTo(stimulus.Receiver));
            Assert.That(myExpectation.Id, Is.EqualTo(StimuliProducesResponseExpectation.CreateId(stimulus, expectedResponse)));
        }

        [Test]
        public void Test_ExpectationNegative()
        {
            var observer = new Observer();
            var sender = new Party("Stuart");
            var receiver = new Party("Jenny");

            // create a stimulus from sender -> receiver
            var stimulus = new ContactsStimulus(sender, receiver);

            var expectedResponse = new ContactResponse("aResponse", receiver);
            var unexpectedResponse = new ContactResponse("bResponse", receiver);

            // Create an expectation
            var myExpectation = new StimuliProducesResponseExpectation(stimulus, expectedResponse);

            var observation = observer.Observe(stimulus, expectedResponse);
            var observation2 = observer.Observe(stimulus, unexpectedResponse);

            Assert.That(myExpectation.Match(observation), Is.True);
            Assert.That(myExpectation.Match(observation2), Is.False);

        }

        [Test]
        public void Test_ExpectationExistsPatternMatcher()
        {
            var observer = new Observer();
            var sender1 = new Party("sender1");
            var sender2 = new Party("sender1");
            var sender3 = new Party("sender1");
            var receiver1 = new Party("receiver1");
            var receiver2 = new Party("receiver2");
            var receiver3 = new Party("receiver3");
            
            var stimulus1 = new ContactsStimulus(sender1, receiver1);
            var stimulus2 = new ContactsStimulus(sender2, receiver2);
            var stimulus3 = new ContactsStimulus(sender3, receiver3);

            var response1 = new ContactResponse("Response1", receiver1);
            var response2 = new ContactResponse("Response2", receiver2);
            var response3 = new ContactResponse("Response3", receiver3);
            
            // Multiple observations occur ...
            observer.Observe(stimulus1, response1);
            observer.Observe(stimulus2, response2);
            observer.Observe(stimulus3, response3);
            
            // Make an observational expectation
            var myExpectation1 = new StimuliProducesResponseExpectation(stimulus2, response2);
            
            // Check if the expectation exists in observations
            var matcher = new ExpectationExistsPatternMatcher(myExpectation1, observer.Observations);
            Assert.That(matcher.Match(), Is.True);

        }

        [Test]
        public void Test_SequentialMatches()
        {
            var observer = new Observer();
            var sender1 = new Party("sender1");
            var sender2 = new Party("sender1");
            var sender3 = new Party("sender1");
            var receiver1 = new Party("receiver1");
            var receiver2 = new Party("receiver2");
            var receiver3 = new Party("receiver3");
            
            var stimulus1 = new ContactsStimulus(sender1, receiver1);
            var stimulus2 = new ContactsStimulus(sender2, receiver2);
            var stimulus3 = new ContactsStimulus(sender3, receiver3);

            var response1 = new ContactResponse("Response1", receiver1);
            var response2 = new ContactResponse("Response2", receiver2);
            var response3 = new ContactResponse("Response3", receiver3);
            
            // Make observations ob some behaviors between sender and receiver
            observer.Observe(stimulus1, response1);
            observer.Observe(stimulus2, response2);
            observer.Observe(stimulus3, response3);

            var myExpectation1 = new StimuliProducesResponseExpectation(stimulus1, response1);
            var myExpectation2 = new StimuliProducesResponseExpectation(stimulus2, response2);
            var myExpectation3 = new StimuliProducesResponseExpectation(stimulus3, response3);

            // Expect that the expectations were met sequentially, i.e that their was a specific sequence of expected outcomes
            var matcher1 = new SequentialExpectedObservationsPattern(new List<IExpectation>(new []{myExpectation1, myExpectation2, myExpectation3}), observer.Observations);
            var matcher2 = new SequentialExpectedObservationsPattern(new List<IExpectation>(new []{myExpectation1,  myExpectation3, myExpectation2}), observer.Observations);

            Assert.That(matcher1.Match(), Is.True);
            Assert.That(matcher2.Match(), Is.False);
        }

        [Test]
        public void Test_OrderedMatches()
        {
            // The observer will consume or observe circumstances (circumstantial observations)
            var observer = new Observer();
            var sender1 = new Party("sender1");
            var sender2 = new Party("sender2");
            var sender3 = new Party("sender3");
            var sender4 = new Party("sender4");
            var sender5 = new Party("sender5");
            var sender6 = new Party("sender6");
            var receiver1 = new Party("receiver1");
            var receiver2 = new Party("receiver2");
            var receiver3 = new Party("receiver3");
            var receiver4 = new Party("receiver4");
            var receiver5 = new Party("receiver5");
            var receiver6 = new Party("receiver6");
            
            var stimulus1 = new ContactsStimulus(sender1, receiver1);
            var stimulus2 = new ContactsStimulus(sender2, receiver2);
            var stimulus3 = new ContactsStimulus(sender3, receiver3);
            var stimulus4 = new ContactsStimulus(sender4, receiver4);
            var stimulus5 = new ContactsStimulus(sender5, receiver5);
            var stimulus6 = new ContactsStimulus(sender6, receiver6);

            // A response by a receiver is uniquely identified and differentiated by the specific response context the receiver produces/exhibits
            var response1 = new ContactResponse("Response1", receiver1);
            var response2 = new ContactResponse("Response2", receiver2);
            var response3 = new ContactResponse("Response3", receiver3);
            var response4 = new ContactResponse("Response4", receiver4);
            var response5 = new ContactResponse("Response5", receiver5);
            var response6 = new ContactResponse("Response6", receiver6);

            // We represent circumstances as specific outcomes/responses that the receiver makes in response to the stimuli from the sender
            var circumstance1 = new ContactCircumstance(stimulus1, response1.Context);
            var circumstance2 = new ContactCircumstance(stimulus2, response2.Context);
            var circumstance3 = new ContactCircumstance(stimulus3, response3.Context);
            var circumstance4 = new ContactCircumstance(stimulus4, response4.Context);
            var circumstance5 = new ContactCircumstance(stimulus5, response5.Context);
            var circumstance6 = new ContactCircumstance(stimulus6, response6.Context);
            
            // Simulate/Observe some circumstances (outcomes)...
            observer.Observe(circumstance1); // 1) we expect 
            observer.Observe(circumstance2); // ignore other - note we can also use a circumstance to represent a specific response made by a receiver stimulated by a sender
            observer.Observe(circumstance3); // 3) we expect this to occur after 1)
            observer.Observe(circumstance3); // ignore dup
            observer.Observe(circumstance3); // ignore dup
            observer.Observe(circumstance4); // 4) we expect this to occur after 3)
            observer.Observe(circumstance5); // we ignore

            // Make some expectations/predictions about that circumstances should have occurred
            var myExpectation1 = new StimuliProducesResponseExpectation(circumstance1);
            var myExpectation3 = new StimuliProducesResponseExpectation(circumstance3);
            var myExpectation4 = new StimuliProducesResponseExpectation(circumstance4);

            // Define a situation where an order in which those predictions were expected to occur in
            var orderOfExpectedOutcomes = new List<IExpectation>(new[] { myExpectation1, myExpectation3, myExpectation4 });

            // Test: ensure the each expected outcomes/prediction come sometime after the prior (doesn't have to be sequentially, but must come after the previous expected outcome)
            var matcher1 = new OrderedExpectedObservationsPattern(orderOfExpectedOutcomes, observer.Observations);

            Assert.That(matcher1.Match(), Is.True);
            Assert.That(matcher1.MatchedExpectations.SequenceEqual(new[] { myExpectation1, myExpectation3, myExpectation4 }));
            Assert.That(matcher1.UnmatchedExpectations, Is.Empty);

            // negative case: Some expectations are not met

            observer = new Observer();


            var myExpectation5 = new StimuliProducesResponseExpectation(circumstance5);
            var myExpectation6 = new StimuliProducesResponseExpectation(circumstance6);

            matcher1 = new OrderedExpectedObservationsPattern(new List<IExpectation>(new []{myExpectation1, myExpectation3, myExpectation4, myExpectation5, myExpectation6}), observer.Observations);
            
            observer.Observe(stimulus1, response1); // we expect
            observer.Observe(stimulus2, response2); // ignore other
            observer.Observe(stimulus3, response3); // we expect
            observer.Observe(stimulus3, response3); // ignore dup
            observer.Observe(stimulus3, response3); // ignore dup
            observer.Observe(stimulus4, response4); // we expect
            // missing expectation 5
            // missing expectation 6

            // The expected observational behavior was not found
            Assert.That(matcher1.Match(), Is.False);

            // We have the first 3 matched expectations correct
            Assert.That(matcher1.MatchedExpectations.SequenceEqual(new[] { myExpectation1, myExpectation3, myExpectation4 }));

            // We did not match expectations 5 and 6
            Assert.That(matcher1.UnmatchedExpectations.SequenceEqual(new[] { myExpectation5, myExpectation6}));
        }
        

        [Test]
        public void Test_ExpectedTestSituationFlowPass()
        {
            var cloudRequester = new Party("cloudRequesterId");
            var onPremComponent = new Party( "onPremComponentId");
            var primaryNode = new Party( "primaryNodeId");
            var secondaryNode = new Party("secondaryNodeId");

            const string transactionId = "NewTxnId123";

            // Model a specific hard-coded situation as the ordered expected behavior of 4 specific parties  
            var flow = new ExpectedTestSituation(transactionId, cloudRequester, onPremComponent, primaryNode, secondaryNode);

            var contactSituation1 = ContactCircumstanceBuilder.Build(cloudRequester, onPremComponent, transactionId, overrideFrom: primaryNode);
            var contactSituation2 = ContactCircumstanceBuilder.Build(primaryNode, secondaryNode, transactionId);
            var contactSituation3 = ContactCircumstanceBuilder.Build(secondaryNode, primaryNode, transactionId);
            var contactSituation4 = ContactCircumstanceBuilder.Build(primaryNode, cloudRequester, transactionId);

            var overseer = new Observer();

            overseer.Observe(contactSituation1); // cloudRequester -> onPremComponent
            overseer.Observe(contactSituation2); // primary -> secondary
            overseer.Observe(contactSituation3); // secondary -> primary
            overseer.Observe(contactSituation4); // primary -> cloudRequester

            Assert.That(flow.Match(overseer.Observations), Is.True);
            Assert.That(flow.GetUnmatchedExpectations(), Is.Empty);
            Assert.That(flow.GetMatchedExpectations().Count, Is.EqualTo(4));
            Assert.That(flow.ToString(), Is.Not.Empty);
        }

        [Test]
        public void Test_ExpectedTestSituationFlowFail()
        {
            var party1 = new Party("party1");
            var party2 = new Party( "party2");
            var party3 = new Party( "party3");
            var party4 = new Party("party4");

            const string transactionId = "NewTxnId123";
            var flow = new ExpectedTestSituation(transactionId, party1, party2, party3, party4);

            var contactSituation1 = ContactCircumstanceBuilder.Build(party1, party2, transactionId, overrideFrom: party3);
            // var contactSituation2 = ContactCircumstanceBuilder.Build(party3, party4, transactionId);
            // var contactSituation3 = ContactCircumstanceBuilder.Build(party4, party3, transactionId);
            var contactSituation4 = ContactCircumstanceBuilder.Build(party3, party1, transactionId);

            var overseer = new Observer();

            overseer.Observe(contactSituation1); // party1 -> party2 (expectation order matched)
            // overseer.Observe(contactSituation2); // party3 -> party4 (expectation not found, tf not met)
            // overseer.Observe(contactSituation3); // party4 -> party3 (expectation not found, tf not met)
            overseer.Observe(contactSituation4); // party3 -> party1 (expectation out of order (needs to occur after exepctation3 but occurs after expectation1))
            
            Assert.That(flow.Match(overseer.Observations), Is.False);
            Assert.That(flow.GetUnmatchedExpectations().Count, Is.EqualTo(3)); // three expectations were either not present (#2,#3) or out of order (#4 - must happen after 3 and doesn't)
            Assert.That(flow.GetMatchedExpectations().Count, Is.EqualTo(1)); // only expectation #1 happens in order (and is present)
            Assert.That(flow.ToString(), Is.Not.Empty);
        }

        [Test]
        public void Test_ContextualFlowsMonitor()
        {
            const string transactionId = "NewTxnId123";
            var overseer = ContextualFlowsMonitor.GetOverseer(transactionId);

            const string testSenderId = "testSenderId";
            const string testReceiverId = "testReceiverId";

            var circumstance1 = MakeContactCircumstance(testSenderId, testReceiverId, transactionId);
            var circumstance2 = MakeContactCircumstance(testSenderId, testReceiverId, transactionId);
            var circumstance3 = MakeContactCircumstance(testSenderId, testReceiverId, transactionId);
            
            overseer.Observe(circumstance1);
            overseer.Observe(circumstance2);

            ContextualFlowsMonitor.RemoveOverseer(transactionId);
            overseer = ContextualFlowsMonitor.GetOverseer(transactionId);
            Assert.That(overseer.Observations, Is.Empty);
            ContextualFlowsMonitor.RemoveOverseer(transactionId);
            
            overseer = ContextualFlowsMonitor.GetOverseer(transactionId);
            overseer.Observe(circumstance3);
            Assert.That(overseer.Observations.Count, Is.EqualTo(1));
            
            ContextualFlowsMonitor.RemoveOverseer(transactionId);
        }

        ContactCircumstance MakeContactCircumstance(string senderId, string receiverId, string contextualResponseId)
        {
            var testSender = new Party(senderId);
            var testReceiver = new Party(receiverId);
            var stimuli = new ContactsStimulus(testSender, testReceiver);
            return new ContactCircumstance(stimuli, contextualResponseId, testReceiver);
        }

    }

}
