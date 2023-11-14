namespace ExpectationLib;

/// <summary>
/// A pattern matcher that expects observations to meet a list expectation that must occur in order
/// <remarks>Other observations that do not meet expectation can occur in between</remarks>
/// </summary>
public class OrderedExpectedObservationsPattern : IExpectatedObservationsPattern
{
    /// <summary>
    ///  A matcher that expects observations to meet a list expectation that must occur in order
    /// </summary>
    /// <param name="expectations">Expectations where each must not match before the prior expectation</param>
    /// <param name="observations">observations that must match the list of ordered expectations</param>
    public OrderedExpectedObservationsPattern(List<IExpectation> expectations, List<Observation> observations)
    {
        Expectations = expectations;
        Observations = observations;
    }

    /// <summary>
    /// Expectations
    /// </summary>
    public List<Observation> Observations { get;  }

    /// <summary>
    /// Expectations
    /// </summary>
    public List<IExpectation> Expectations { get; }

    /// <summary>
    /// Unmatched expectations
    /// </summary>
    public List<IExpectation> UnmatchedExpectations => Expectations.Except(MatchedExpectations).ToList();

    /// <summary>
    /// Matched expectations
    /// </summary>
    public List<IExpectation> MatchedExpectations { get; } = new();

    /// <inheritdoc />
    public bool Match()
    {
        var countMatches = 0;
        int i = 0;
        
        foreach (var observation in Observations)
        {
            if (i > Expectations.Count-1 ) continue;
            if (!Expectations[i].Match(observation)) continue; // can have other unmatched observations in between
            MatchedExpectations.Add(Expectations[i]);                
            i++;
            countMatches++;
        }

        return countMatches == Expectations.Count;
    }
}