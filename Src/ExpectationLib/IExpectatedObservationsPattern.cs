namespace ExpectationLib;

/// <summary>
/// Pattern of behavior that all ExpectationObservationsPatterns should have
/// </summary>
public interface IExpectatedObservationsPattern
{
    /// <summary>
    /// Ability to indicate if it resulted in a match or not
    /// </summary>
    /// <returns></returns>
    public bool Match();
}