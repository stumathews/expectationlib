using System.Text;

namespace ExpectationLib;

/// <summary>
/// The expected behavior of observations for the test situation
/// </summary>
public class ExpectedTestSituation : ISituation
{
    public string TransactionId { get; }
    public IParty CloudRequester { get; }
    public IParty OnPremComponent { get; }
    public IParty PrimaryNode { get; }
    public IParty SecondaryNode { get; }
    
    public const string CloudRequesterRoleName = "CloudRequester";
    public const string OnPremComponentRoleName = "OnPremComponent";
    public const string PrimaryNodeRoleName = "PrimaryNode";
    public const string SecondaryNodeRoleName = "SecondaryNode";

    public List<IExpectation> UnmatchedExpectations { get; private set; }
    public List<IExpectation> MatchedExpectations { get; private set; }

    public ExpectedTestSituation(string transactionId, IParty cloudRequester, IParty onPremComponent, IParty primaryNode, IParty secondaryNode)
    {
        TransactionId = transactionId;
        CloudRequester = cloudRequester;
        OnPremComponent = onPremComponent;
        PrimaryNode = primaryNode;
        SecondaryNode = secondaryNode;

        Setup();
    }

    public override string ToString()
    {
        var sb = new StringBuilder();
        var i = 0;
        foreach (var expectation in MatchedExpectations)
        {
            sb.Append($" #{++i}: Expectation: {expectation} \n");
        }

        i = 0;
        foreach (var expectation in UnmatchedExpectations)
        {
            sb.Append($" #{++i}: Expectation: {expectation} ** Unmatched ** \n");
        }
        return sb.ToString();
    }



    private void Setup()
    {
    }

    ///<inheritdoc /> 
    public bool Match(List<Observation> observations)
    {

        
        // Expected behavior is an ordered match of specific Stimuli-Response pairs:

        // cloudRequester -> onPremComponent
        // primary -> secondary
        // secondary -> primary
        // primary -> cloudRequester

        var sharedResponseContext = TransactionId;

        var contactSituation1 = ContactCircumstanceBuilder.Build(CloudRequester, OnPremComponent, sharedResponseContext, PrimaryNode);
        var contactSituation2 = ContactCircumstanceBuilder.Build(PrimaryNode, SecondaryNode, sharedResponseContext);
        var contactSituation3 = ContactCircumstanceBuilder.Build(SecondaryNode, PrimaryNode, sharedResponseContext );
        var contactSituation4 = ContactCircumstanceBuilder.Build(PrimaryNode, CloudRequester, sharedResponseContext);
        
        var expect1 = new StimuliMatchesResponseExpectation(contactSituation1.Stimulus, contactSituation1.Response);
        var expect2 = new StimuliMatchesResponseExpectation(contactSituation2.Stimulus, contactSituation2.Response);
        var expect3 = new StimuliMatchesResponseExpectation(contactSituation3.Stimulus, contactSituation3.Response);
        var expect4 = new StimuliMatchesResponseExpectation(contactSituation4.Stimulus, contactSituation4.Response);
        
        var orderedExpectations = new List<IExpectation> { expect1, expect2, expect3, expect4 };

        // The expected behavior of this situation is that there is an ordered observation of StimuliMatchesResponse expectations
        var matcher = new OrderedExpectedObservationsPattern(orderedExpectations, observations);
        
        var wasMatch = matcher.Match();
        
        UnmatchedExpectations = matcher.UnmatchedExpectations;
        MatchedExpectations = matcher.MatchedExpectations;

        return wasMatch;
    }
}