namespace ExpectationLib
{

    public class StimuliMatchesResponseExpectation : IExpectation, IHasId
    {
        /// <summary>
        /// Stimuli that is expected to cause the associated Response
        /// </summary>
        public IStimulus Stimuli { get; }

        /// <summary>
        /// The response that is expected to occur in response to receiving a specific Stimuli
        /// </summary>
        public IResponse Response { get; }

        /// <summary>
        /// The expectation's unique Identifier
        /// </summary>
        public string Id => CreateId(Stimuli, Response);

        /// <summary>
        /// Ctor
        /// </summary>
        /// <param name="stimuli">Stimuli</param>
        /// <param name="response">Response</param>
        public StimuliMatchesResponseExpectation(IStimulus stimuli, IResponse response)
        {
            Stimuli = stimuli;
            Response = response;
        }

        /// <summary>
        /// String representation of an expectation
        /// <remarks>Usually for logging purposes</remarks>
        /// </summary>
        /// <returns></returns>
        public override string ToString() => $"{Stimuli} (Response: {Response})";

        /// <summary>
        /// Reconstruct an Expectation's ID.
        /// </summary>
        /// <param name="stimuli"></param>
        /// <param name="response"></param>
        /// <returns></returns>
        public static string CreateId(IStimulus stimuli, IResponse response) => $"{stimuli.Sender.Id}{stimuli.Receiver.Id}{response.Id}";

        /// <inheritdoc />
        public bool Match(Observation observation)
        {
            return observation.Stimulus.Sender.Equals(Stimuli.Sender) &&
                   observation.Stimulus.Receiver.Equals(Stimuli.Receiver) &&
                   observation.Response.Equals(Response);
        }
       
        #region Comparison code
        protected bool Equals(StimuliMatchesResponseExpectation other) => Equals(Stimuli, other.Stimuli) && Equals(Response, other.Response);

        public override bool Equals(object obj)
        {
            if (ReferenceEquals(null, obj)) return false;
            if (ReferenceEquals(this, obj)) return true;
            if (obj.GetType() != this.GetType()) return false;
            return Equals((StimuliMatchesResponseExpectation)obj);
        }

        public override int GetHashCode()
        {
            return HashCode.Combine(Stimuli, Response);
        }

        #endregion
    }
}
