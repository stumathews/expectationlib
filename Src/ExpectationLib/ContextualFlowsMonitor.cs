using System.Collections.Concurrent;

namespace ExpectationLib;

/// <summary>
/// A Singleton that holds Overseers indexed by a specific context that the overseer is observing
/// </summary>
public class ContextualFlowsMonitor
{
    private ContextualFlowsMonitor() { }

    /// <summary>
    /// Access to ContextualFlowsMonitor
    /// </summary>
    public static ContextualFlowsMonitor Instance => instance ??= new ContextualFlowsMonitor();
    
    /// <summary>
    /// Fetch a specific Overseer
    /// </summary>
    /// <param name="context">The context that this overseer is pertinent to</param>
    /// <returns>Overseer</returns>
    public static Overseer GetOverseer(string context) => Instance.GetOverseerInternal(context);

    /// <summary>
    /// Removes an overseer
    /// </summary>
    /// <param name="context">Identify which overseer to remove</param>
    /// <returns></returns>
    public static bool RemoveOverseer(string context) =>
        Instance._contextualOverseer.TryRemove(context, out var removed);

    private Overseer GetOverseerInternal(string context)
    {
        if (_contextualOverseer.TryGetValue(context, out var overseer))
        {
            return overseer;
        }

        _contextualOverseer.TryAdd(context, new Overseer());
        return GetOverseerInternal(context);
            
    }

    protected static ContextualFlowsMonitor instance = null;

    private readonly ConcurrentDictionary<string, Overseer> _contextualOverseer = new();
}