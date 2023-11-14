namespace ExpectationLib;

/// <summary>
/// An Observation is an observed association between a Stimuli and a Response
/// </summary>
public class Observation : IHasId
{
    /// <summary>
    /// The Stimulus
    /// </summary>
    public IStimulus Stimulus { get; }

    /// <summary>
    /// The Response
    /// </summary>
    public IResponse Response { get; }

    protected bool Equals(Observation other)
    {
        return Equals(Stimulus, other.Stimulus) && Equals(Response, other.Response) && Context == other.Context;
    }

    public override bool Equals(object obj)
    {
        if (ReferenceEquals(null, obj)) return false;
        if (ReferenceEquals(this, obj)) return true;
        if (obj.GetType() != this.GetType()) return false;
        return Equals((Observation)obj);
    }

    public override int GetHashCode()
    {
        return HashCode.Combine(Stimulus, Response, Context);
    }

    /// <summary>
    /// Observational Context
    /// </summary>
    public string Context { get; }

    public Observation(IStimulus stimulus, IResponse response, string context)
    {
        Stimulus = stimulus;
        Response = response;
        Context = context;
    }

    public Observation(ICircumstance circumstance, string context) : this(circumstance.Stimulus, circumstance.Response, context)
    {
        
    }

    /// <summary>
    /// Reconstruct an Observation Id from its constituent parts
    /// </summary>
    /// <param name="stimulus">Stimulus</param>
    /// <param name="response">Response</param>
    /// <returns></returns>
    public static string CreateId(IStimulus stimulus, IResponse response) => $"{stimulus.Sender.Id}{stimulus.Receiver.Id}{response.From.Id}{response.Id}";

    /// <inheritdoc />
    public string Id => CreateId(Stimulus, Response);
}