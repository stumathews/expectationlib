using System.Text;

namespace ExpectationLib;

/// <summary>
/// The test situation's behavior is an ordered set of specific circumstances
/// </summary>
public class ExpectedTestSituation : ISituation
{
    public string TransactionId { get; }
    
    public IParty Party1 { get; }
    public IParty Party2 { get; }
    public IParty Party3 { get; }
    public IParty Party4 { get; }

    public List<IExpectation> GetMatchedExpectations() => _matchedExpectations;
    public List<IExpectation> GetUnmatchedExpectations() => _unmatchedExpectations;

    public ExpectedTestSituation(string transactionId, IParty party1, IParty party2, IParty party3, IParty party4)
    {
        TransactionId = transactionId;
        Party1 = party1;
        Party2 = party2;
        Party3 = party3;
        Party4 = party4;
    }

    public override string ToString()
    {
        var sb = new StringBuilder();
        var i = 0;
        foreach (var expectation in _matchedExpectations)
        {
            sb.Append($" #{++i}: Expectation: {expectation} \n");
        }

        i = 0;
        foreach (var expectation in _unmatchedExpectations)
        {
            sb.Append($" #{++i}: Expectation: {expectation} ** Unmatched ** \n");
        }
        return sb.ToString();
    }
    
    ///<inheritdoc /> 
    public bool Match(List<Observation> observations)
    {
        // Expected behavior is an ordered set of specific circumstances:

        // party1 -> party2
        // party3 -> party4
        // party4 -> party3
        // party3 -> party1

        var sharedResponseContext = TransactionId;

        var contactCircumstance1 = ContactCircumstanceBuilder.Build(Party1, Party2, sharedResponseContext, Party3);
        var contactCircumstance2 = ContactCircumstanceBuilder.Build(Party3, Party4, sharedResponseContext);
        var contactCircumstance3 = ContactCircumstanceBuilder.Build(Party4, Party3, sharedResponseContext );
        var contactCircumstance4 = ContactCircumstanceBuilder.Build(Party3, Party1, sharedResponseContext);
        
        var expect1 = new StimuliProducesResponseExpectation(contactCircumstance1);
        var expect2 = new StimuliProducesResponseExpectation(contactCircumstance2);
        var expect3 = new StimuliProducesResponseExpectation(contactCircumstance3);
        var expect4 = new StimuliProducesResponseExpectation(contactCircumstance4);
        
        var orderedExpectations = new List<IExpectation> { expect1, expect2, expect3, expect4 };

        // The expected behavior of this situation is that there is an ordered observation of StimuliMatchesResponse expectations
        var matcher = new OrderedExpectedObservationsPattern(orderedExpectations, observations);
        
        var wasMatch = matcher.Match();
        
        _unmatchedExpectations = matcher.UnmatchedExpectations;
        _matchedExpectations = matcher.MatchedExpectations;

        return wasMatch;
    }

    private List<IExpectation> _matchedExpectations = new();
    private List<IExpectation> _unmatchedExpectations = new();
}