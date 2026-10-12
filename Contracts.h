#pragma once
#include <random>
#include <string>



enum class ContractType {
    SPEED_RECORD,
    PAYLOAD_DELIVERY,
    SUBORBITAL_FLIGHT
};

class Contracts {
private:
    int ID;
    ContractType type;
    std::string title;
    std::string description;

    double target_velocity_mps;
    double target_altitude_km;
    double target_payload_mass_kg;

    double advance_payment;
    double payment;
    double final_payment;
    double reputation;
    double penalty;
    double deadline_days;
    double rep_success;
    double rep_failure;

    bool isActive = false;
    bool isCompleted = false;
    bool isFailed = false;
public:
    Contracts();
    Contracts(
    int ID, ContractType type, std::string title, std::string description, double target_velocity_mps,
    double target_altitude_km, double target_payload_mass_kg, double advance_payment, double payment,  double final_payment,
    double reputation, double penalty, double deadline_days, double rep_success, double rep_failure, bool isActive, bool isCompleted, bool isFailed);


    bool checkCompletion(double max_velocity_mps, double max_altitude_km, double max_payload_mass_kg) const;
    static Contracts  generateContract(double reputation);

    int getId() const;
    ContractType getContractType() const;
    std::string getTitle() const;
    std::string getDescription() const;

    double get_target_velocity_mps() const;
    double get_target_altitude_km() const;
    double get_target_payload_mass_kg() const;


    double getAdvance() const;
    double getPayment() const;
    double getFinalPayment() const;
    double getPenalty() const;
    double getReputation() const;
    double getDeadline() const;
    double getRepSuccess() const;
    double getRepFailure() const;
    void setIsActive(bool state);
    void setIsFailed(bool state);



};



