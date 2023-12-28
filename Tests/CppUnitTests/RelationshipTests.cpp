#include "pch.h"
#include "pch.h"

#include "ContactCircumstance.h"
#include "ContactResponse.h"
#include "ContactStimulus.h"
#include "Observer.h"
#include "Ordering.h"
#include "Party.h"
#include "StimuliProducesResponseExpectation.h"

using namespace ExpectationLib;

TEST(RelationshipTests, RelationIsSet)
{

	const auto observer = std::make_shared<Observer>();
	auto sender = std::make_shared<Party>("Stuart");
	auto receiver = std::make_shared<Party>("Jenny");

	// create a certain kind of stimulus Mechanosensory (Contact) from sender -> receiver
	const std::shared_ptr<IStimulus> stimulus = std::make_shared<ContactsStimulus>(sender, receiver); // should this modify the sender/receiver to manipulate the effect this had on its state?
	
	// Perform a stimulus .. sender contacts receiver and a contact response is produced
	// make sure the observer observes it: Create a stimulus that produces a response when it is observed
	observer->Observe(stimulus);

	EXPECT_EQ(sender->GetRelations().size(), 1);
	EXPECT_EQ(receiver->GetRelations().size(), 1);

	EXPECT_EQ(receiver->GetRelations()[0].Name, ContactResponse::ContactRelationName);
	EXPECT_EQ(receiver->GetRelations()[0].To, sender);
	EXPECT_EQ(sender->GetRelations()[0].Name, ContactResponse::ContactRelationName);
	EXPECT_EQ(sender->GetRelations()[0].To, receiver);

	EXPECT_TRUE(sender->HasRelationTo(receiver, ContactResponse::ContactRelationName));
	EXPECT_TRUE(receiver->HasRelationTo(sender, ContactResponse::ContactRelationName));
	
}