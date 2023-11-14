namespace ExpectationLib;

/// <summary>
/// A sender or of recipient of a stimulus
/// </summary>
public interface IParty: IHasId
{
    /// <summary>
    /// A general, non-unique role that the party plays.
    /// <remarks>Eg. 'Accountant' or 'Logging System'</remarks>
    /// </summary>
    public string Role { get; }
}