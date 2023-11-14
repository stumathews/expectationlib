namespace ExpectationLib;

/// <summary>
/// A matcher that expects observations to meet expectation that must occur in sequential order
/// <remarks>No other observations can occur</remarks>
/// </summary>
public class SequentialExpectedObservationsPattern : IExpectatedObservationsPattern
{
    /// <summary>
    /// list of expectations
    /// </summary>
    public List<IExpectation> Expectations { get; }

    /// <summary>
    /// list of observations
    /// </summary>
    public List<Observation> Observations { get; }

    /// <summary>
    /// A matcher that expects observations to meet expectation that must occur in sequential order
    /// </summary>
    /// <param name="expectations">A list of sequential expectations that must be met in order of observations</param>
    /// <param name="observations">observations that must meet the associated expectation strictly one after the other</param>
    public SequentialExpectedObservationsPattern(List<IExpectation> expectations, List<Observation> observations)
    {
        Expectations = expectations;
        Observations = observations;
    }
    /// <inheritdoc />
    public bool Match()
    {
        if (Expectations.Count != Observations.Count) return false;
        for (var i = 0; i < Expectations.Count; i++)
        {
            if (!Expectations[i].Match(Observations[i])) return false;
        }

        return true;
    }
}