#include <string>


namespace ExpectationLib
{
    
class Party : public IParty {
public:
    std::string id;
    std::string role;

    Party(std::string id, std::string role = "") {
        this->id = id;
        this->role = role;
    }

    std::string getId() {
        return id;
    }

    std::string getRole() {
        return role;
    }

    bool operator==(const Party& other) const {
        return id == other.id && role == other.role;
    }

    std::string Role() override;
};
}
