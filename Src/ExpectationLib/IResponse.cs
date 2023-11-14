namespace ExpectationLib;

/// <summary>
/// A response is an action that occurs as a result of a stimuli
/// </summary>
public interface IResponse : IHasId
{
    /// <summary>
    /// The party that produced the response
    /// </summary>
    public IParty From { get; set; }

    /// <summary>
    /// The response's context
    /// <remarks>This can hold unique response information that can distinguish this form other responses</remarks>
    /// </summary>
    public string Context { get; set; }
}