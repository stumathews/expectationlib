namespace ExpectationLib;

/// <summary>
/// An observer of observations
/// </summary>
public interface IOverseer
{
    /// <summary>
    /// Observe a stimuli and response pair
    /// </summary>
    /// <param name="stimulus">Stimuli</param>
    /// <param name="response">Associated Response</param>
    /// <param name="context">Observational Context, i.e information captured at the time of observation</param>
    /// <returns>Observation</returns>
    Observation Observe(IStimulus stimulus, IResponse response, string context = null);
}