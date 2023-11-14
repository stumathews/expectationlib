namespace ExpectationLib;

/// <summary>
/// Easily create circumstances for contact situations
/// </summary>
public class ContactCircumstanceBuilder : ISituationBuilder
{
    /// <summary>
    /// Build a contact circumstance
    /// </summary>
    /// <param name="sender">Sender</param>
    /// <param name="receiver">Receiver</param>
    /// <param name="responseContext">Response context</param>
    /// <param name="overrideFrom">Change the origin of the response</param>
    /// <returns></returns>
    public static ContactCircumstance Build(IParty sender, IParty receiver, string responseContext, IParty overrideFrom = null) 
        => new (new ContactsStimulus(sender, receiver), responseContext, overrideFrom);
}