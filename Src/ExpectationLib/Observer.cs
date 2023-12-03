using System.Text;

namespace ExpectationLib;

public class Observer: IOverseer
{
    private readonly object _lockObject = new();
    public List<Observation> Observations { get; } = new();
        
    public Observation Observe(IStimulus stimulus, IResponse response, string context = "")
    {
        lock (_lockObject)
        {
            var observation = new Observation(stimulus, response, context);
            Observations.Add(observation);
            return observation;
        }
    }

    public Observation Observe(ICircumstance circumstance, string context = null) => Observe(circumstance.Stimulus, circumstance.Response, context);

    public override string ToString()
    {
        var sb = new StringBuilder();
        var i = 0;
        foreach (var observation in Observations)
        {
            sb.Append($" #{++i}: {observation.Stimulus.Sender.Role} -> {observation.Stimulus.Receiver.Role} (Response Context: {observation.Response.Context}) (Observation Context: {observation.Context})\n");
        }
        return sb.ToString();
    }
}