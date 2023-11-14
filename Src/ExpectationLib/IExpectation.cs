namespace ExpectationLib;

/// <summary>
/// An expectation the requirement for an observation 
/// </summary>
public interface IExpectation
{
    /// <summary>
    /// Check of an observation matches the expectation of the observation
    /// </summary>
    /// <param name="observation">Observation</param>
    /// <returns>True if the observation meets the requirements of the expectation</returns>
    public bool Match(Observation observation);
}