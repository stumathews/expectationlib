namespace ExpectationLib;

/// <summary>
/// A matcher that expects an observation that meets an expectation to exist
/// </summary>
public class ExpectationExistsPatternMatcher : IExpectatedObservationsPattern
{
    public StimuliProducesResponseExpectation StimuliProducesResponseExpectation { get; }
    public List<Observation> Observations { get; }

    public ExpectationExistsPatternMatcher(StimuliProducesResponseExpectation stimuliProducesResponseExpectation, List<Observation> observations)
    {
        StimuliProducesResponseExpectation = stimuliProducesResponseExpectation;
        Observations = observations;
    }

    public bool Match()
    {
        return Observations.Any(o => o.Stimulus.Sender.Id.Equals(StimuliProducesResponseExpectation.Stimuli.Sender.Id) &&
                                     o.Stimulus.Receiver.Id.Equals(StimuliProducesResponseExpectation.Stimuli.Receiver.Id) &&
                                     o.Response.Id.Equals(StimuliProducesResponseExpectation.Response.Id));
    }
}