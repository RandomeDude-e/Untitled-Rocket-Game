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


    [[nodiscard]] bool checkCompletion(double max_velocity_mps, double max_altitude_km, double max_payload_mass_kg) const;
    static Contracts  generateContract(double reputation);

    [[nodiscard]] int getId() const;
    [[nodiscard]] ContractType getContractType() const;
    [[nodiscard]] std::string getTitle() const;
    [[nodiscard]] std::string getDescription() const;

    [[nodiscard]] double get_target_velocity_mps() const;
    [[nodiscard]] double get_target_altitude_km() const;
    [[nodiscard]] double get_target_payload_mass_kg() const;


    [[nodiscard]] double getAdvance() const;
    [[nodiscard]] double getPayment() const;
    [[nodiscard]] double getFinalPayment() const;
    [[nodiscard]] double getPenalty() const;
    [[nodiscard]] double getReputation() const;
    [[nodiscard]] double getDeadline() const;
    [[nodiscard]] double getRepSuccess() const;
    [[nodiscard]] double getRepFailure() const;
    void setIsActive(bool state);
    void setIsFailed(bool state);



};



