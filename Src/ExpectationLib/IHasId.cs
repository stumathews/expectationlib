namespace ExpectationLib;

/// <summary>
/// The ability to identify oneself with an Identification identifier. 
/// </summary>
public interface IHasId
{
    /// <summary>
    /// Identifier
    /// <remarks>Usually unique but this is not imposed.</remarks>
    /// </summary>
    public string Id { get; }
}