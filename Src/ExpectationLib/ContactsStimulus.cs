namespace ExpectationLib;

/// <summary>
/// A contact stimulus is a generic action that occurs when a sender makes contact with a receiver
/// </summary>
public class ContactsStimulus : IStimulus
{
    /// <inheritdoc />
    public IParty Sender { get; }

    /// <inheritdoc />
    public IParty Receiver { get; }

    public ContactsStimulus(IParty sender, IParty receiver)
    {
        Sender = sender;
        Receiver = receiver;
    }

    public override string ToString() => $"Contact Stimulus: {Sender.Role} -> {Receiver.Role}";

    public static string CreateId(IParty sender, IParty receiver) => $"{sender.Id} -> {receiver.Id}";
    
    /// <inheritdoc />
    public string Id => CreateId(Sender, Receiver);
}