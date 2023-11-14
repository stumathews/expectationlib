namespace ExpectationLib;

/// <summary>
/// A matcher that expects an observation that meets an expectation to exist
/// </summary>
public class ExpectedObservationsExistsPattern : IExpectatedObservationsPattern
{
    public StimuliMatchesResponseExpectation StimuliMatchesResponseExpectation { get; }
    public List<Observation> Observations { get; }

    public ExpectedObservationsExistsPattern(StimuliMatchesResponseExpectation stimuliMatchesResponseExpectation, List<Observation> observations)
    {
        StimuliMatchesResponseExpectation = stimuliMatchesResponseExpectation;
        Observations = observations;
    }

    public bool Match()
    {
        return Observations.Any(o => o.Stimulus.Sender.Id.Equals(StimuliMatchesResponseExpectation.Stimuli.Sender.Id) &&
                                     o.Stimulus.Receiver.Id.Equals(StimuliMatchesResponseExpectation.Stimuli.Receiver.Id) &&
                                     o.Response.Id.Equals(StimuliMatchesResponseExpectation.Response.Id));
    }
}