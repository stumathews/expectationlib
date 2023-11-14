namespace ExpectationLib;

/// <summary>
/// A circumstance represents a particular response to a stimulus
/// </summary>
public interface ICircumstance
{
    /// <summary>
    /// Stimulus
    /// </summary>
    public IStimulus Stimulus { get; }

    /// <summary>
    /// Response
    /// </summary>
    public IResponse Response { get; }
}