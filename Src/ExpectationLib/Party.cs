namespace ExpectationLib;

/// <summary>
/// Convenience class that identifies a Party as a Sender 
/// </summary>
public class Party: IParty
{
    public Party(string id, string role = "")
    {
        Id = id;
        Role = role;
    }

    /// <inheritdoc /> 
    public string Id { get; }

    /// <inheritdoc /> 
    public string Role { get; }

    #region Comparison code
    protected bool Equals(Party other)
    {
        return Id == other.Id && Role == other.Role;
    }

    public override bool Equals(object obj)
    {
        if (ReferenceEquals(null, obj)) return false;
        if (ReferenceEquals(this, obj)) return true;
        if (obj.GetType() != this.GetType()) return false;
        return Equals((Party)obj);
    }
    public override int GetHashCode()
    {
        return HashCode.Combine(Id, Role);
    }
    #endregion
}