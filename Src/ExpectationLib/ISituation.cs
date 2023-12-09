namespace ExpectationLib;

/// <summary>
/// A situation is a specific coordinated collection circumstances
/// </summary>
public interface ISituation
{
    /// <summary>
    /// Tests if the observations represent the situation
    /// </summary>
    /// <param name="observations"></param>
    /// <returns></returns>
    public bool Match(List<Observation> observations);
}