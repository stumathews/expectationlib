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
            var observer = new Overseer();
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
            var observer = new Overseer();
            var sender = new Party("Stuart");
            var receiver = new Party("Jenny");

            // create a stimulus from sender -> receiver
            var stimulus = new ContactsStimulus(sender, receiver);

            var expectedResponse = new ContactResponse("aResponse", receiver);

            // Create an expectation
            var myExpectation = new StimuliMatchesResponseExpectation(stimulus, expectedResponse);
            // perform a stimulus ..
            
            // make sure the observer observes it
            observer.Observe(stimulus, expectedResponse);

            // Ensure the expectation is met by observations

            Assert.That(myExpectation.Stimuli, Is.EqualTo(stimulus));
            Assert.That(myExpectation.Stimuli.Sender, Is.EqualTo(stimulus.Sender));
            Assert.That(myExpectation.Stimuli.Receiver, Is.EqualTo(stimulus.Receiver));
            Assert.That(myExpectation.Id, Is.EqualTo(StimuliMatchesResponseExpectation.CreateId(stimulus, expectedResponse)));
        }

        [Test]
        public void Test_SingleObservationMatcher()
        {
            var observer = new Overseer();
            var sender = new Party("Stuart");
            var receiver = new Party("Jenny");

            // create a stimulus from sender -> receiver
            var stimulus = new ContactsStimulus(sender, receiver);

            var expectedResponse = new ContactResponse("aResponse", receiver);
            var unexpectedResponse = new ContactResponse("bResponse", receiver);

            // Create an expectation
            var myExpectation = new StimuliMatchesResponseExpectation(stimulus, expectedResponse);

            var observation = observer.Observe(stimulus, expectedResponse);
            var observation2 = observer.Observe(stimulus, unexpectedResponse);

            Assert.That(myExpectation.Match(observation), Is.True);
            Assert.That(myExpectation.Match(observation2), Is.False);

        }

        [Test]
        public void Test_ExpectationExistsMatcher()
        {
            var observer = new Overseer();
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
            
            observer.Observe(stimulus1, response1);
            observer.Observe(stimulus2, response2);
            observer.Observe(stimulus3, response3);

            
            var myExpectation1 = new StimuliMatchesResponseExpectation(stimulus2, response2);

            var matcher = new ExpectedObservationsExistsPattern(myExpectation1, observer.Observations);
            Assert.That(matcher.Match(), Is.True);

        }

        [Test]
        public void Test_SequentialMatches()
        {
            var observer = new Overseer();
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
            
            observer.Observe(stimulus1, response1);
            observer.Observe(stimulus2, response2);
            observer.Observe(stimulus3, response3);

            var myExpectation1 = new StimuliMatchesResponseExpectation(stimulus1, response1);
            var myExpectation2 = new StimuliMatchesResponseExpectation(stimulus2, response2);
            var myExpectation3 = new StimuliMatchesResponseExpectation(stimulus3, response3);

            var matcher1 = new SequentialExpectedObservationsPattern(new List<IExpectation>(new []{myExpectation1, myExpectation2, myExpectation3}), observer.Observations);
            var matcher2 = new SequentialExpectedObservationsPattern(new List<IExpectation>(new []{myExpectation1,  myExpectation3, myExpectation2}), observer.Observations);

            Assert.That(matcher1.Match(), Is.True);
            Assert.That(matcher2.Match(), Is.False);
        }

        [Test]
        public void Test_OrderedMatches()
        {
            var observer = new Overseer();
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

            var response1 = new ContactResponse("Response1", receiver1);
            var response2 = new ContactResponse("Response2", receiver2);
            var response3 = new ContactResponse("Response3", receiver3);
            var response4 = new ContactResponse("Response4", receiver4);
            var response5 = new ContactResponse("Response5", receiver5);
            var response6 = new ContactResponse("Response6", receiver6);
            
            observer.Observe(stimulus1, response1); // we expect
            observer.Observe(stimulus2, response2); // ignore other
            observer.Observe(stimulus3, response3); // we expect
            observer.Observe(stimulus3, response3); // ignore dup
            observer.Observe(stimulus3, response3); // ignore dup
            observer.Observe(stimulus4, response4); // we expect
            observer.Observe(stimulus5, response5); // we ignore

            var myExpectation1 = new StimuliMatchesResponseExpectation(stimulus1, response1);
            var myExpectation3 = new StimuliMatchesResponseExpectation(stimulus3, response3);
            var myExpectation4 = new StimuliMatchesResponseExpectation(stimulus4, response4);

            var matcher1 = new OrderedExpectedObservationsPattern(new List<IExpectation>(new []{myExpectation1, myExpectation3, myExpectation4}), observer.Observations);

            Assert.That(matcher1.Match(), Is.True);

            Assert.That(matcher1.MatchedExpectations.SequenceEqual(new[] { myExpectation1, myExpectation3, myExpectation4 }));
            Assert.That(matcher1.UnmatchedExpectations, Is.Empty);

            // negative case: Some expectations are not met

            observer = new Overseer();

            observer.Observe(stimulus1, response1); // we expect
            observer.Observe(stimulus2, response2); // ignore other
            observer.Observe(stimulus3, response3); // we expect
            observer.Observe(stimulus3, response3); // ignore dup
            observer.Observe(stimulus3, response3); // ignore dup
            observer.Observe(stimulus4, response4); // we expect
            // missing expectation 5
            // missing expectation 6

            
            var myExpectation5 = new StimuliMatchesResponseExpectation(stimulus5, response5);
            var myExpectation6 = new StimuliMatchesResponseExpectation(stimulus6, response6);

            matcher1 = new OrderedExpectedObservationsPattern(new List<IExpectation>(new []{myExpectation1, myExpectation3, myExpectation4, myExpectation5, myExpectation6}), observer.Observations);
            
            Assert.That(matcher1.Match(), Is.False);

            Assert.That(matcher1.MatchedExpectations.SequenceEqual(new[] { myExpectation1, myExpectation3, myExpectation4 }));

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
            var flow = new ExpectedTestSituation(transactionId, cloudRequester, onPremComponent, primaryNode, secondaryNode);

            var contactSituation1 = ContactCircumstanceBuilder.Build(cloudRequester, onPremComponent, transactionId, overrideFrom: primaryNode);
            var contactSituation2 = ContactCircumstanceBuilder.Build(primaryNode, secondaryNode, transactionId);
            var contactSituation3 = ContactCircumstanceBuilder.Build(secondaryNode, primaryNode, transactionId);
            var contactSituation4 = ContactCircumstanceBuilder.Build(primaryNode, cloudRequester, transactionId);

            var overseer = new Overseer();

            overseer.Observe(contactSituation1); // cloudRequester -> onPremComponent
            overseer.Observe(contactSituation2); // primary -> secondary
            overseer.Observe(contactSituation3); // secondary -> primary
            overseer.Observe(contactSituation4); // primary -> cloudRequester

            Assert.That(flow.Match(overseer.Observations), Is.True);
            Assert.That(flow.UnmatchedExpectations, Is.Empty);
            Assert.That(flow.MatchedExpectations.Count, Is.EqualTo(4));
            Assert.That(flow.ToString(), Is.Not.Empty);
        }

        [Test]
        public void Test_ExpectedTestSituationFlowFail()
        {
            var cloudRequester = new Party("cloudRequesterId");
            var onPremComponent = new Party( "onPremComponentId");
            var primaryNode = new Party( "primaryNodeId");
            var secondaryNode = new Party("secondaryNodeId");

            const string transactionId = "NewTxnId123";
            var flow = new ExpectedTestSituation(transactionId, cloudRequester, onPremComponent, primaryNode, secondaryNode);

            var contactSituation1 = ContactCircumstanceBuilder.Build(cloudRequester, onPremComponent, transactionId, overrideFrom: primaryNode);
            var contactSituation2 = ContactCircumstanceBuilder.Build(primaryNode, secondaryNode, transactionId);
            var contactSituation3 = ContactCircumstanceBuilder.Build(secondaryNode, primaryNode, transactionId);
            var contactSituation4 = ContactCircumstanceBuilder.Build(primaryNode, cloudRequester, transactionId);

            var overseer = new Overseer();

            overseer.Observe(contactSituation1); // cloudRequester -> onPremComponent (expectation order matched)
            //overseer.Observe(contactSituation2); // primary -> secondary (expectation not found, tf not met)
            // overseer.Observe(contactSituation3); // secondary -> primary (expectation not found, tf not met)
            overseer.Observe(contactSituation4); // primary -> cloudRequester (expectation out of order (needs to occur after exepctation3 but occurs after expectation1))
            
            Assert.That(flow.Match(overseer.Observations), Is.False);
            Assert.That(flow.UnmatchedExpectations.Count, Is.EqualTo(3)); // three expectations were either not present (#2,#3) or out of order (#4 - must happen after 3 and doesn't)
            Assert.That(flow.MatchedExpectations.Count, Is.EqualTo(1)); // only expectation #1 happens in order (and is present)
            Assert.That(flow.ToString(), Is.Not.Empty);
        }

        [Test]
        public void Test_ContextualFlowsMonitor()
        {
            const string transactionId = "NewTxnId123";
            var overseer = ContextualFlowsMonitor.GetOverseer(transactionId);

            var testSenderId = "testSenderId";
            var testReceiverId = "testReceiverId";

            var circumstance1 = MakeTestContactStimulus(testSenderId, testReceiverId, transactionId);
            var circumstance2 = MakeTestContactStimulus(testSenderId, testReceiverId, transactionId);
            var circumstance3 = MakeTestContactStimulus(testSenderId, testReceiverId, transactionId);
            
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

        ContactCircumstance MakeTestContactStimulus(string senderId, string receiverId, string contextualResponseId)
        {
            var testSender = new Party(senderId);
            var testReceiver = new Party(receiverId);
            var stimuli = new ContactsStimulus(testSender, testReceiver);
            return new ContactCircumstance(stimuli, contextualResponseId, testReceiver);
        }

    }

}
