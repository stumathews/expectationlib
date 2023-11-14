namespace ExpectationLib;

/// <summary>
/// A situation a list of expectations that observations must meet to in order to represent that situation
/// </summary>
public interface ISituation
{
    /// <summary>
    /// Tests if the observations meet the expectations of a situation/flow
    /// </summary>
    /// <param name="observations"></param>
    /// <returns></returns>
    public bool Match(List<Observation> observations);
}