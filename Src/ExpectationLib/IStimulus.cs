namespace ExpectationLib;

/// <summary>
/// A stimulus represents an action taken by a sender that is directed at a receiver
/// </summary>
public interface IStimulus : IHasId
{
    /// <summary>
    /// The initiator of the stimulus
    /// </summary>
    public IParty Sender { get; }

    /// <summary>
    /// The recipient of the stimulus
    /// </summary>
    public IParty Receiver { get; }
}