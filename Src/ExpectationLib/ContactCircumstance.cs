namespace ExpectationLib;

/// <summary>
/// A particular response to a contact stimulus 
/// </summary>
public class ContactCircumstance : ICircumstance
{
    /// <inheritdoc />
    public IStimulus Stimulus { get; }
    
    /// <inheritdoc />
    public IResponse Response => new ContactResponse(_responseContext, From);
    
    private IParty From { get; }
    private readonly string _responseContext;

    public ContactCircumstance(IStimulus stimulus, string responseContext, IParty overrideFrom = null)
    {
        Stimulus = stimulus;
        From = overrideFrom ?? Stimulus.Receiver;
        _responseContext = responseContext;
    }
}