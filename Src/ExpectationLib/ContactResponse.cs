namespace ExpectationLib;

/// <summary>
/// A response in response to a contact stimulus
/// </summary>
public class ContactResponse: IResponse
{
    /// <summary>
    /// A response in response to a contact stimulus
    /// </summary>
    /// <param name="context">Response context/details</param>
    /// <param name="from">Usualy the response is from the receiver of the stimulus, but this can be overriden here</param>
    public ContactResponse(string context, IParty from)
    {
        From = from;
        Context = context;
    }

    /// <inheritdoc />
    public IParty From { get; set; }

    /// <inheritdoc />
    public string Context { get; set; }
    public string CreateId(string context, IParty from) => $"{context}{from.Id}";

    public override string ToString() => $"{Context}";

    public string Id => CreateId(Context, From);

    #region Comparison code
    protected bool Equals(ContactResponse other)
    {
        return Equals(From, other.From) && Context == other.Context;
    }

    public override bool Equals(object obj)
    {
        if (ReferenceEquals(null, obj)) return false;
        if (ReferenceEquals(this, obj)) return true;
        if (obj.GetType() != this.GetType()) return false;
        return Equals((ContactResponse)obj);
    }

    public override int GetHashCode()
    {
        return HashCode.Combine(From, Context);
    }
    #endregion
}