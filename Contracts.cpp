#include "Contracts.h"

Contracts::Contracts():
        ID(0), type(ContractType::SPEED_RECORD), title(" ") , description(" ") , target_velocity_mps(0.0),
        target_altitude_km(0.0), target_payload_mass_kg(0.0), advance_payment(0), payment(0), final_payment(0), reputation(0), penalty(0),
        deadline_days(0),rep_success(0), rep_failure(0),isActive(false), isCompleted(false), isFailed(false){}

Contracts::Contracts(int ID, ContractType type,std::string title, std::string description, double target_velocity_mps,
          double target_altitude_km, double target_payload_mass_kg, double advance_payment, double payment, double final_payment, double reputation, double penalty,
          double deadline_days,double rep_success, double rep_failure,  bool isActive, bool isCompleted, bool isFailed):
                ID(ID), type(type), title{std::move(title)}, description{std::move(description)},  target_velocity_mps(target_velocity_mps),
                target_altitude_km(target_altitude_km),target_payload_mass_kg(target_payload_mass_kg),advance_payment(advance_payment),
                payment(payment), final_payment(final_payment), reputation(reputation), penalty(penalty), deadline_days(deadline_days), rep_success(rep_success), rep_failure(rep_failure), isActive(isActive), isCompleted(isCompleted),isFailed(isFailed){}





bool Contracts::checkCompletion(double max_velocity_mps, double max_altitude_km, double max_payload_mass_kg) const{
    if (!isActive || isFailed) return false;
    switch (type) {
        case ContractType::SPEED_RECORD:
            return max_velocity_mps>=target_velocity_mps;
        case ContractType::SUBORBITAL_FLIGHT:
            return max_altitude_km>=target_altitude_km;
        case ContractType::PAYLOAD_DELIVERY:
            return max_payload_mass_kg>=target_payload_mass_kg;
        default:
            return false;

    }
}

Contracts Contracts::generateContract(double rep) {
    Contracts c;
    double rep_coef = rep / 100.0;
    if (rep_coef <=0.1) rep_coef = 0.1;

    static std::random_device rd;
    static std::mt19937 gen(rd());
    constexpr int q_types = 3;
    static int current_id = 0;
    c.type = static_cast<ContractType>(gen() % q_types);

    double difficulty = std::pow(rep_coef, 0.7);

    switch (c.type) {
        case ContractType::SPEED_RECORD:
            c.target_velocity_mps = static_cast<int>(300 + 1000 * difficulty);
            c.title = "Рекорд скорости";
            c.description = "Компания Roman Inc. поручает Вам новое задание.Выведите ракету на скорость "+
                    std::to_string(c.target_velocity_mps) +
                        "м/с\n";
            c.payment = 1000 * rep_coef;
            c.advance_payment = c.payment * 0.2;
            c.final_payment = c.payment - c.advance_payment;
            c.penalty = (c.payment * 0.5) + c.advance_payment;
            c.rep_success = std::max(1, static_cast<int>(10 * rep_coef));
            c.rep_failure = std::max(1, static_cast<int>(std::round(c.rep_success * 1.5)));
            c.deadline_days = 5+(30 * rep_coef);
            break;

        case ContractType::SUBORBITAL_FLIGHT:
            c.target_altitude_km = static_cast<int>(5+35*difficulty);
            c.title = "Суборбитальный полёт";
            c.description = "Компания Roman Inc. поручает Вам выполнить суборбитальный полёт. "
                          "Выведите ракету на высоту " +
                          std::to_string(c.target_altitude_km) +
                          " км и успешно завершите миссию.\n";

            c.payment = 3000 * rep_coef;
            c.advance_payment = c.payment * 0.2;
            c.final_payment = c.payment - c.advance_payment;
            c.penalty = (c.payment * 0.5) + c.advance_payment;
            c.rep_success = std::max(1, static_cast<int>(15 * rep_coef));
            c.rep_failure = std::max(1, static_cast<int>(std::round(c.rep_success * 1.5)));
            c.deadline_days = 10 + (25 * rep_coef);
            break;

        case ContractType::PAYLOAD_DELIVERY:
            c.target_payload_mass_kg = static_cast<int>(20+30*difficulty);
            c.title = "Доставка полезной нагрузки";
            c.description = "Компания Roman Inc. поручает Вам доставить полезную нагрузку массой " +
                          std::to_string(c.target_payload_mass_kg) +
                          " кг в заданную точку назначения. Обеспечьте успешный запуск "
                          "и безопасную доставку груза.\n";

            c.payment = 2500 * rep_coef;
            c.advance_payment = c.payment * 0.2;
            c.final_payment = c.payment - c.advance_payment;
            c.penalty = (c.payment * 0.5) + c.advance_payment;
            c.rep_success = std::max(1, static_cast<int>(12 * rep_coef));
            c.rep_failure = std::max(1, static_cast<int>(std::round(c.rep_success * 1.5)));
            c.deadline_days = 7 + (20 * rep_coef);
            break;

        default:
            break;


    }
    c.ID = ++current_id;
    return c;
}

int Contracts::getId() const {
    return ID;
}
ContractType Contracts::getContractType() const {
    return type;
}
std::string Contracts::getTitle() const {
    return title;
}
std::string Contracts::getDescription() const {
    return description;
}
double Contracts::get_target_velocity_mps() const {
    return target_velocity_mps;
}
double Contracts::get_target_altitude_km() const {
    return target_altitude_km;
}
double Contracts::get_target_payload_mass_kg() const {
    return target_payload_mass_kg;
}
double Contracts::getAdvance() const {
    return advance_payment;
}
double Contracts::getPayment() const {
    return payment;
}
double Contracts::getFinalPayment() const {
    return final_payment;
}
double Contracts::getPenalty() const {
    return penalty;
}
double Contracts::getReputation() const {
    return reputation;
}
double Contracts::getDeadline() const {
    return deadline_days;
}
double Contracts::getRepSuccess() const {
    return rep_success;
}
double Contracts::getRepFailure() const {
    return rep_failure;
}
void Contracts::setIsActive(bool state)  {
    isActive = state;
}
void Contracts::setIsFailed(bool state) {
    isFailed = state;
}
