#include <iostream>
#include <string>
#include <limits>
#include <fstream>
#include <sstream>

using namespace std;

//  CONSTANTES
const int MAX_PATIENTS = 100;
const int MAX_MEDECINS = 50;
const int MAX_INFIRMIERS = 50;
const int MAX_RENDEZVOUS = 200;
const int MAX_ADMISSIONS = 100;
const int MAX_EQUIPEMENTS = 100;
const int MAX_PRESCRIPTIONS = 200;
const int MAX_MEDICAMENTS = 100;

//  CLASSES DE BASE

class Rendezvous {
protected:
    int idRDV;
    string dateRDV;
    string heureRDV;
    string motifRDV;
    int idPaiement;
    int idService;
    int idPatient;

public:
    Rendezvous() : idRDV(0), idPaiement(0), idService(0), idPatient(0) {}

    Rendezvous(int idRDV, string dateRDV, string heureRDV, string motifRDV)
        : idRDV(idRDV), dateRDV(dateRDV), heureRDV(heureRDV), motifRDV(motifRDV),
          idPaiement(0), idService(0), idPatient(0) {}

    void afficher() {
        cout << "\n--- Rendez-vous ---" << endl;
        cout << "ID RDV: " << idRDV << endl;
        cout << "Date: " << dateRDV << endl;
        cout << "Heure: " << heureRDV << endl;
        cout << "Motif: " << motifRDV << endl;
    }

    int getId() const { return idRDV; }
    string getDate() const { return dateRDV; }
    string getHeure() const { return heureRDV; }
    string getMotif() const { return motifRDV; }
    ~Rendezvous() {}
};

class Paiement {
private:
    int idPaiement;
    float montant;
    string datePaiement;
    string mode;

public:
    Paiement() : idPaiement(0), montant(0.0) {}

    Paiement(int idPaiement, float montant, string datePaiement, string mode)
        : idPaiement(idPaiement), montant(montant), datePaiement(datePaiement), mode(mode) {}

    void afficherPaiement() {
        cout << "\n--- Paiement ---" << endl;
        cout << "ID: " << idPaiement << endl;
        cout << "Montant: " << montant << " DH" << endl;
        cout << "Mode: " << mode << endl;
        cout << "Date: " << datePaiement << endl;
    }

    int getId() const { return idPaiement; }
    ~Paiement() {}
};

class Service {
private:
    int idService;
    string nom;
    string telService;

public:
    Service() : idService(0) {}

    Service(int idService, string nom, string telService)
        : idService(idService), nom(nom), telService(telService) {}

    void afficher() {
        cout << "\n--- Service ---" << endl;
        cout << "ID Service: " << idService << endl;
        cout << "Nom: " << nom << endl;
        cout << "Telephone: " << telService << endl;
    }

    int getId() const { return idService; }
    ~Service() {}
};

class Notification {
private:
    int idNotif;
    string date_denvoie;
    string message;
    bool statut;

public:
    Notification() : idNotif(0), statut(false) {}

    Notification(int idNotif, string date_denvoie, string message, bool statut)
        : idNotif(idNotif), date_denvoie(date_denvoie), message(message), statut(statut) {}

    void afficher() {
        cout << "\n--- Notification ---" << endl;
        cout << "ID: " << idNotif << endl;
        cout << "Date d'envoi: " << date_denvoie << endl;
        cout << "Message: " << message << endl;
        cout << "Statut: " << (statut ? "Recu" : "Non recu") << endl;
    }

    int getId() const { return idNotif; }
    ~Notification() {}
};

class Equipement {
private:
    int id;
    string nom;
    string type;
    enum EtatEquipement { FONCTIONNEL, EN_PANNE, EN_MAINTENANCE };
    EtatEquipement etat;

public:
    Equipement() : id(0), etat(FONCTIONNEL) {}

    Equipement(int id, string nom, string type, int etatInt)
        : id(id), nom(nom), type(type) {
        etat = static_cast<EtatEquipement>(etatInt);
    }

    void afficher() {
        cout << "\n--- Equipement ---" << endl;
        cout << "ID: " << id << endl;
        cout << "Nom: " << nom << endl;
        cout << "Type: " << type << endl;
        cout << "Etat: ";
        switch(etat) {
            case FONCTIONNEL: cout << "Fonctionnel"; break;
            case EN_PANNE: cout << "En panne"; break;
            case EN_MAINTENANCE: cout << "En maintenance"; break;
        }
        cout << endl;
    }

    int getId() const { return id; }
    string getNom() const { return nom; }
    string getType() const { return type; }
    int getEtat() const { return etat; }
    ~Equipement() {}
};

class Patient {
protected:
    int id_patient;
    string nom;
    string prenom;
    string num_cin;
    int id_dossier;

public:
    Patient() : id_patient(0), id_dossier(0) {}

    Patient(int id_patient, string nom, string prenom, string num_cin, int id_dossier)
        : id_patient(id_patient), nom(nom), prenom(prenom), num_cin(num_cin), id_dossier(id_dossier) {}

    void afficherPatient() {
        cout << "\n--- Patient ---" << endl;
        cout << "ID: " << id_patient << endl;
        cout << "Nom: " << nom << endl;
        cout << "Prenom: " << prenom << endl;
        cout << "CIN: " << num_cin << endl;
        cout << "ID Dossier: " << id_dossier << endl;
    }

    int getId() const { return id_patient; }
    string getNom() const { return nom; }
    string getPrenom() const { return prenom; }
    string getCIN() const { return num_cin; }
    int getIdDossier() const { return id_dossier; }
    ~Patient() {}
};

class Dossier {
protected:
    int id_dossier;
    string date_creation;
    string date_MAJ;

public:
    Dossier() : id_dossier(0) {}

    Dossier(int id_dossier, string date_creation, string date_MAJ)
        : id_dossier(id_dossier), date_creation(date_creation), date_MAJ(date_MAJ) {}

    void afficherDossier() {
        cout << "\n--- Dossier Medical ---" << endl;
        cout << "ID Dossier: " << id_dossier << endl;
        cout << "Date de creation: " << date_creation << endl;
        cout << "Date de MAJ: " << date_MAJ << endl;
    }

    int getId() const { return id_dossier; }
    ~Dossier() {}
};

class Admission {
protected:
    int id_admission;
    string date_admission;
    string etat_patient;
    int id_lit;

public:
    Admission() : id_admission(0), id_lit(0) {}

    Admission(int id_admission, string date_admission, string etat_patient, int id_lit)
        : id_admission(id_admission), date_admission(date_admission),
          etat_patient(etat_patient), id_lit(id_lit) {}

    void afficherAdmission() {
        cout << "\n--- Admission ---" << endl;
        cout << "ID Admission: " << id_admission << endl;
        cout << "Date: " << date_admission << endl;
        cout << "Etat du patient: " << etat_patient << endl;
        cout << "ID Lit: " << id_lit << endl;
    }

    int getId() const { return id_admission; }
    string getDate() const { return date_admission; }
    string getEtat() const { return etat_patient; }
    int getIdLit() const { return id_lit; }
    ~Admission() {}
};

class Intervention {
protected:
    int id_interv;
    string date_interv;
    string heure_debut;
    string heure_fin;

public:
    Intervention() : id_interv(0) {}

    Intervention(int id_interv, string date_interv, string heure_debut, string heure_fin)
        : id_interv(id_interv), date_interv(date_interv),
          heure_debut(heure_debut), heure_fin(heure_fin) {}

    void afficherIntervention() {
        cout << "\n--- Intervention ---" << endl;
        cout << "ID: " << id_interv << endl;
        cout << "Date: " << date_interv << endl;
        cout << "Heure debut: " << heure_debut << endl;
        cout << "Heure fin: " << heure_fin << endl;
    }

    int getId() const { return id_interv; }
    ~Intervention() {}
};

class Contrat {
protected:
    int id_contrat;
    string typecontrat;
    string date_debut;
    string date_fin;

public:
    Contrat() : id_contrat(0) {}

    Contrat(int id_contrat, string typecontrat, string date_debut, string date_fin)
        : id_contrat(id_contrat), typecontrat(typecontrat),
          date_debut(date_debut), date_fin(date_fin) {}

    void afficherContrat() {
        cout << "\n--- Contrat ---" << endl;
        cout << "ID: " << id_contrat << endl;
        cout << "Type: " << typecontrat << endl;
        cout << "Date debut: " << date_debut << endl;
        cout << "Date fin: " << date_fin << endl;
    }

    int getId() const { return id_contrat; }
    ~Contrat() {}
};


class Departement {
protected:
    string nom_dept;
    string localisation;

public:
    Departement() {}
    Departement(string nom_dept, string localisation)
        : nom_dept(nom_dept), localisation(localisation) {}

    virtual void afficher_info() {
        cout << "\n--- Departement ---" << endl;
        cout << "Nom: " << nom_dept << endl;
        cout << "Localisation: " << localisation << endl;
    }

    virtual ~Departement() {}
};

class Chambre : public Departement {
private:
    int numero_chambre;
    int nb_lits;

public:
    Chambre() : numero_chambre(0), nb_lits(0) {}

    Chambre(string nom_dept, string localisation, int numero_chambre, int nb_lits)
        : Departement(nom_dept, localisation), numero_chambre(numero_chambre), nb_lits(nb_lits) {}

    void afficher_info() override {
        Departement::afficher_info();
        cout << "Numero de chambre: " << numero_chambre << endl;
        cout << "Nombre de lits: " << nb_lits << endl;
    }

    ~Chambre() {}
};

class BlocOperatoire : public Departement {
private:
    int numero_bloc;
    int nb_salles;

public:
    BlocOperatoire() : numero_bloc(0), nb_salles(0) {}

    BlocOperatoire(string nom_dept, string localisation, int numero_bloc, int nb_salles)
        : Departement(nom_dept, localisation), numero_bloc(numero_bloc), nb_salles(nb_salles) {}

    void afficher_info() override {
        Departement::afficher_info();
        cout << "Numero de bloc: " << numero_bloc << endl;
        cout << "Nombre de salles: " << nb_salles << endl;
    }

    ~BlocOperatoire() {}
};


class Prescription {
private:
    int id_prescription;
    string date_prescription;
    string details;

public:
    Prescription() : id_prescription(0) {}

    Prescription(int id_prescription, string date_prescription, string details)
        : id_prescription(id_prescription), date_prescription(date_prescription), details(details) {}

    void afficher_presc() {
        cout << "\n--- Prescription ---" << endl;
        cout << "ID: " << id_prescription << endl;
        cout << "Date: " << date_prescription << endl;
        cout << "Details: " << details << endl;
    }

    int getId() const { return id_prescription; }
    string getDate() const { return date_prescription; }
    string getDetails() const { return details; }
    ~Prescription() {}
};

class Soin {
private:
    int id_soin;
    string nom_soin;
    string description;

public:
    Soin() : id_soin(0) {}

    Soin(int id_soin, string nom_soin, string description)
        : id_soin(id_soin), nom_soin(nom_soin), description(description) {}

    void afficher_soin() {
        cout << "\n--- Soin ---" << endl;
        cout << "ID: " << id_soin << endl;
        cout << "Nom: " << nom_soin << endl;
        cout << "Description: " << description << endl;
    }

    int getId() const { return id_soin; }
    ~Soin() {}
};

class Medicament {
private:
    int id_medicament;
    string nom_medicament;
    string posologie;

public:
    Medicament() : id_medicament(0) {}

    Medicament(int id_medicament, string nom_medicament, string posologie)
        : id_medicament(id_medicament), nom_medicament(nom_medicament), posologie(posologie) {}

    void afficher_medic() {
        cout << "\n--- Medicament ---" << endl;
        cout << "ID: " << id_medicament << endl;
        cout << "Nom: " << nom_medicament << endl;
        cout << "Posologie: " << posologie << endl;
    }

    int getId() const { return id_medicament; }
    string getNom() const { return nom_medicament; }
    string getPosologie() const { return posologie; }
    ~Medicament() {}
};

class Maintenance {
private:
    int id_maintenance;
    string date_maintenance;
    string description;

public:
    Maintenance() : id_maintenance(0) {}

    Maintenance(int id_maintenance, string date_maintenance, string description)
        : id_maintenance(id_maintenance), date_maintenance(date_maintenance), description(description) {}

    void afficher_maint() {
        cout << "\n--- Maintenance ---" << endl;
        cout << "ID: " << id_maintenance << endl;
        cout << "Date: " << date_maintenance << endl;
        cout << "Description: " << description << endl;
    }

    int getId() const { return id_maintenance; }
    ~Maintenance() {}
};



class Employee {
protected:
    int id;
    string nom;
    string prenom;
    string date_N;
    bool sexe;
    string email;
    string date_E;
    double salaire;

public:
    Employee() : id(0), sexe(true), salaire(0.0) {}

    Employee(int id, string nom, string prenom, string date_N, bool sexe,
             string email, string date_E, double salaire)
        : id(id), nom(nom), prenom(prenom), date_N(date_N), sexe(sexe),
          email(email), date_E(date_E), salaire(salaire) {}

    virtual void afficher_emp() {
        cout << "\n--- Employe ---" << endl;
        cout << "ID: " << id << endl;
        cout << "Nom: " << nom << endl;
        cout << "Prenom: " << prenom << endl;
        cout << "Date de naissance: " << date_N << endl;
        cout << "Sexe: " << (sexe ? "Homme" : "Femme") << endl;
        cout << "Email: " << email << endl;
        cout << "Date d'embauche: " << date_E << endl;
        cout << "Salaire: " << salaire << " DH" << endl;
    }

    int getId() const { return id; }
    string getNom() const { return nom; }
    string getPrenom() const { return prenom; }
    string getDateNaissance() const { return date_N; }
    bool getSexe() const { return sexe; }
    string getEmail() const { return email; }
    string getDateEmbauche() const { return date_E; }
    double getSalaire() const { return salaire; }
    virtual ~Employee() {}
};

class Infirmier : public Employee {
private:
    string service;

public:
    Infirmier() {}

    Infirmier(int id, string nom, string prenom, string date_N, bool sexe,
              string email, string date_E, double salaire, string service)
        : Employee(id, nom, prenom, date_N, sexe, email, date_E, salaire), service(service) {}

    void afficher_emp() override {
        Employee::afficher_emp();
        cout << "Service: " << service << endl;
    }

    ~Infirmier() {}
};

class Medecin : public Employee {
private:
    string specialite;

public:
    Medecin() {}

    Medecin(int id, string nom, string prenom, string date_N, bool sexe,
            string email, string date_E, double salaire, string specialite)
        : Employee(id, nom, prenom, date_N, sexe, email, date_E, salaire), specialite(specialite) {}

    void afficher_emp() override {
        Employee::afficher_emp();
        cout << "Specialite: " << specialite << endl;
    }

    string getSpecialite() const { return specialite; }
    ~Medecin() {}
};

class RespoRH : public Employee {
private:
    int nb_recrutements;

public:
    RespoRH() : nb_recrutements(0) {}

    RespoRH(int id, string nom, string prenom, string date_N, bool sexe,
            string email, string date_E, double salaire, int nb_recrutements)
        : Employee(id, nom, prenom, date_N, sexe, email, date_E, salaire),
          nb_recrutements(nb_recrutements) {}

    void afficher_emp() override {
        Employee::afficher_emp();
        cout << "Nombre de recrutements: " << nb_recrutements << endl;
    }

    ~RespoRH() {}
};

class Technicien : public Employee {
private:
    string domaine;

public:
    Technicien() {}

    Technicien(int id, string nom, string prenom, string date_N, bool sexe,
               string email, string date_E, double salaire, string domaine)
        : Employee(id, nom, prenom, date_N, sexe, email, date_E, salaire), domaine(domaine) {}

    void afficher_emp() override {
        Employee::afficher_emp();
        cout << "Domaine: " << domaine << endl;
    }

    ~Technicien() {}
};

class Securite : public Employee {
private:
    string shift;

public:
    Securite() {}

    Securite(int id, string nom, string prenom, string date_N, bool sexe,
             string email, string date_E, double salaire, string shift)
        : Employee(id, nom, prenom, date_N, sexe, email, date_E, salaire), shift(shift) {}

    void afficher_emp() override {
        Employee::afficher_emp();
        cout << "Shift: " << shift << endl;
    }

    ~Securite() {}
};

class AgentAccueil : public Employee {
private:
    string fonction;

public:
    AgentAccueil() {}

    AgentAccueil(int id, string nom, string prenom, string date_N, bool sexe,
                 string email, string date_E, double salaire, string fonction)
        : Employee(id, nom, prenom, date_N, sexe, email, date_E, salaire), fonction(fonction) {}

    void afficher_emp() override {
        Employee::afficher_emp();
        cout << "Fonction: " << fonction << endl;
    }

    ~AgentAccueil() {}
};

class Comptable : public Employee {
private:
    int nb_factures;

public:
    Comptable() : nb_factures(0) {}

    Comptable(int id, string nom, string prenom, string date_N, bool sexe,
              string email, string date_E, double salaire, int nb_factures)
        : Employee(id, nom, prenom, date_N, sexe, email, date_E, salaire),
          nb_factures(nb_factures) {}

    void afficher_emp() override {
        Employee::afficher_emp();
        cout << "Nombre de factures: " << nb_factures << endl;
    }

    ~Comptable() {}
};

//  SYSTEME DE GESTION

class SystemeGestionHospital {
private:
    // Tableaux statiques
    Patient patients[MAX_PATIENTS];
    Medecin medecins[MAX_MEDECINS];
    Infirmier infirmiers[MAX_INFIRMIERS];
    Rendezvous rendezvous[MAX_RENDEZVOUS];
    Admission admissions[MAX_ADMISSIONS];
    Equipement equipements[MAX_EQUIPEMENTS];
    Prescription prescriptions[MAX_PRESCRIPTIONS];
    Medicament medicaments[MAX_MEDICAMENTS];

    // Compteurs
    int nbPatients;
    int nbMedecins;
    int nbInfirmiers;
    int nbRendezvous;
    int nbAdmissions;
    int nbEquipements;
    int nbPrescriptions;
    int nbMedicaments;

    void clearInput() {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

public:
    SystemeGestionHospital() : nbPatients(0), nbMedecins(0), nbInfirmiers(0),
                                nbRendezvous(0), nbAdmissions(0), nbEquipements(0),
                                nbPrescriptions(0), nbMedicaments(0) {}

    void ajouterPatient() {
        if (nbPatients >= MAX_PATIENTS) {
            cout << "\nErreur: Capacite maximale de patients atteinte!" << endl;
            return;
        }

        int id, id_dossier;
        string nom, prenom, num_cin;

        cout << "\n=== Ajouter un Patient ===" << endl;
        cout << "ID Patient: "; cin >> id;
        clearInput();
        cout << "Nom: "; getline(cin, nom);
        cout << "Prenom: "; getline(cin, prenom);
        cout << "CIN: "; getline(cin, num_cin);
        cout << "ID Dossier: "; cin >> id_dossier;

        patients[nbPatients] = Patient(id, nom, prenom, num_cin, id_dossier);
        nbPatients++;
        cout << "\n✓ Patient ajoute avec succes! (Total: " << nbPatients << ")" << endl;
    }

    void afficherPatients() {
        cout << "\n=== Liste des Patients ===" << endl;
        if (nbPatients == 0) {
            cout << "Aucun patient enregistre." << endl;
            return;
        }
        cout << "Nombre total: " << nbPatients << endl;
        for (int i = 0; i < nbPatients; i++) {
            patients[i].afficherPatient();
        }
    }

    void ajouterMedecin() {
        if (nbMedecins >= MAX_MEDECINS) {
            cout << "\nErreur: Capacite maximale de medecins atteinte!" << endl;
            return;
        }

        int id;
        string nom, prenom, date_N, email, date_E, specialite;
        bool sexe;
        double salaire;

        cout << "\n=== Ajouter un Medecin ===" << endl;
        cout << "ID: "; cin >> id;
        clearInput();
        cout << "Nom: "; getline(cin, nom);
        cout << "Prenom: "; getline(cin, prenom);
        cout << "Date naissance (JJ/MM/AAAA): "; getline(cin, date_N);
        cout << "Sexe (1=Homme, 0=Femme): "; cin >> sexe;
        clearInput();
        cout << "Email: "; getline(cin, email);
        cout << "Date embauche (JJ/MM/AAAA): "; getline(cin, date_E);
        cout << "Salaire: "; cin >> salaire;
        clearInput();
        cout << "Specialite: "; getline(cin, specialite);

        medecins[nbMedecins] = Medecin(id, nom, prenom, date_N, sexe, email, date_E, salaire, specialite);
        nbMedecins++;
        cout << "\n✓ Medecin ajoute avec succes! (Total: " << nbMedecins << ")" << endl;
    }

    void afficherMedecins() {
        cout << "\n=== Liste des Medecins ===" << endl;
        if (nbMedecins == 0) {
            cout << "Aucun medecin enregistre." << endl;
            return;
        }
        cout << "Nombre total: " << nbMedecins << endl;
        for (int i = 0; i < nbMedecins; i++) {
            medecins[i].afficher_emp();
        }
    }

    void ajouterRendezvous() {
        if (nbRendezvous >= MAX_RENDEZVOUS) {
            cout << "\nErreur: Capacite maximale de rendez-vous atteinte!" << endl;
            return;
        }

        int id;
        string date, heure, motif;

        cout << "\n=== Ajouter un Rendez-vous ===" << endl;
        cout << "ID RDV: "; cin >> id;
        clearInput();
        cout << "Date (JJ/MM/AAAA): "; getline(cin, date);
        cout << "Heure (HH:MM): "; getline(cin, heure);
        cout << "Motif: "; getline(cin, motif);

        rendezvous[nbRendezvous] = Rendezvous(id, date, heure, motif);
        nbRendezvous++;
        cout << "\n✓ Rendez-vous ajoute avec succes! (Total: " << nbRendezvous << ")" << endl;
    }

    void afficherRendezvous() {
        cout << "\n=== Liste des Rendez-vous ===" << endl;
        if (nbRendezvous == 0) {
            cout << "Aucun rendez-vous enregistre." << endl;
            return;
        }
        cout << "Nombre total: " << nbRendezvous << endl;
        for (int i = 0; i < nbRendezvous; i++) {
            rendezvous[i].afficher();
        }
    }

    void ajouterAdmission() {
        if (nbAdmissions >= MAX_ADMISSIONS) {
            cout << "\nErreur: Capacite maximale d'admissions atteinte!" << endl;
            return;
        }

        int id, id_lit;
        string date, etat;

        cout << "\n=== Ajouter une Admission ===" << endl;
        cout << "ID Admission: "; cin >> id;
        clearInput();
        cout << "Date (JJ/MM/AAAA): "; getline(cin, date);
        cout << "Etat patient: "; getline(cin, etat);
        cout << "ID Lit: "; cin >> id_lit;

        admissions[nbAdmissions] = Admission(id, date, etat, id_lit);
        nbAdmissions++;
        cout << "\n✓ Admission ajoutee avec succes! (Total: " << nbAdmissions << ")" << endl;
    }

    void afficherAdmissions() {
        cout << "\n=== Liste des Admissions ===" << endl;
        if (nbAdmissions == 0) {
            cout << "Aucune admission enregistree." << endl;
            return;
        }
        cout << "Nombre total: " << nbAdmissions << endl;
        for (int i = 0; i < nbAdmissions; i++) {
            admissions[i].afficherAdmission();
        }
    }

    void ajouterEquipement() {
        if (nbEquipements >= MAX_EQUIPEMENTS) {
            cout << "\nErreur: Capacite maximale d'equipements atteinte!" << endl;
            return;
        }

        int id, etat;
        string nom, type;

        cout << "\n=== Ajouter un Equipement ===" << endl;
        cout << "ID: "; cin >> id;
        clearInput();
        cout << "Nom: "; getline(cin, nom);
        cout << "Type: "; getline(cin, type);
        cout << "Etat (0=Fonctionnel, 1=En panne, 2=En maintenance): "; cin >> etat;

        equipements[nbEquipements] = Equipement(id, nom, type, etat);
        nbEquipements++;
        cout << "\n✓ Equipement ajoute avec succes! (Total: " << nbEquipements << ")" << endl;
    }

    void afficherEquipements() {
        cout << "\n=== Liste des Equipements ===" << endl;
        if (nbEquipements == 0) {
            cout << "Aucun equipement enregistre." << endl;
            return;
        }
        cout << "Nombre total: " << nbEquipements << endl;
        for (int i = 0; i < nbEquipements; i++) {
            equipements[i].afficher();
        }
    }

    void ajouterPrescription() {
        if (nbPrescriptions >= MAX_PRESCRIPTIONS) {
            cout << "\nErreur: Capacite maximale de prescriptions atteinte!" << endl;
            return;
        }

        int id;
        string date, details;

        cout << "\n=== Ajouter une Prescription ===" << endl;
        cout << "ID: "; cin >> id;
        clearInput();
        cout << "Date (JJ/MM/AAAA): "; getline(cin, date);
        cout << "Details: "; getline(cin, details);

        prescriptions[nbPrescriptions] = Prescription(id, date, details);
        nbPrescriptions++;
        cout << "\n✓ Prescription ajoutee avec succes! (Total: " << nbPrescriptions << ")" << endl;
    }

    void afficherPrescriptions() {
        cout << "\n=== Liste des Prescriptions ===" << endl;
        if (nbPrescriptions == 0) {
            cout << "Aucune prescription enregistree." << endl;
            return;
        }
        cout << "Nombre total: " << nbPrescriptions << endl;
        for (int i = 0; i < nbPrescriptions; i++) {
            prescriptions[i].afficher_presc();
        }
    }

    void ajouterMedicament() {
        if (nbMedicaments >= MAX_MEDICAMENTS) {
            cout << "\nErreur: Capacite maximale de medicaments atteinte!" << endl;
            return;
        }

        int id;
        string nom, posologie;

        cout << "\n=== Ajouter un Medicament ===" << endl;
        cout << "ID: "; cin >> id;
        clearInput();
        cout << "Nom: "; getline(cin, nom);
        cout << "Posologie: "; getline(cin, posologie);

        medicaments[nbMedicaments] = Medicament(id, nom, posologie);
        nbMedicaments++;
        cout << "\n✓ Medicament ajoute avec succes! (Total: " << nbMedicaments << ")" << endl;
    }

    void afficherMedicaments() {
        cout << "\n=== Liste des Medicaments ===" << endl;
        if (nbMedicaments == 0) {
            cout << "Aucun medicament enregistre." << endl;
            return;
        }
        cout << "Nombre total: " << nbMedicaments << endl;
        for (int i = 0; i < nbMedicaments; i++) {
            medicaments[i].afficher_medic();
        }
    }

    void rechercherPatientParId() {
        if (nbPatients == 0) {
            cout << "\nAucun patient enregistre." << endl;
            return;
        }

        int id;
        cout << "\nEntrez l'ID du patient: ";
        cin >> id;

        bool trouve = false;
        for (int i = 0; i < nbPatients; i++) {
            if (patients[i].getId() == id) {
                patients[i].afficherPatient();
                trouve = true;
                break;
            }
        }

        if (!trouve) {
            cout << "\nPatient non trouve!" << endl;
        }
    }

    void afficherStatistiques() {
        cout << "\n.................................................." << endl;
        cout << ".           STATISTIQUES DU SYSTEME             ." << endl;
        cout << ".................................................." << endl;
        cout << ". Patients:       " << nbPatients << " / " << MAX_PATIENTS << endl;
        cout << ". Medecins:       " << nbMedecins << " / " << MAX_MEDECINS << endl;
        cout << ". Rendez-vous:    " << nbRendezvous << " / " << MAX_RENDEZVOUS << endl;
        cout << ". Admissions:     " << nbAdmissions << " / " << MAX_ADMISSIONS << endl;
        cout << ". Equipements:    " << nbEquipements << " / " << MAX_EQUIPEMENTS << endl;
        cout << ". Prescriptions:  " << nbPrescriptions << " / " << MAX_PRESCRIPTIONS << endl;
        cout << ". Medicaments:    " << nbMedicaments << " / " << MAX_MEDICAMENTS << endl;
        cout << ".................................................." << endl;
    }

    //  SAUVEGARDE CSV

    void sauvegarderPatients() {
        ofstream fichier("patients.csv");
        if (!fichier) {
            cout << "\nErreur: Impossible de creer le fichier patients.csv" << endl;
            return;
        }


        fichier << "ID,Nom,Prenom,CIN,ID_Dossier" << endl;


        for (int i = 0; i < nbPatients; i++) {
            fichier << patients[i].getId() << ","
                    << patients[i].getNom() << ","
                    << patients[i].getPrenom() << ","
                    << patients[i].getCIN() << ","
                    << patients[i].getIdDossier() << endl;
        }

        fichier.close();
        cout << "\n✓ " << nbPatients << " patients sauvegardes dans patients.csv" << endl;
    }

    void sauvegarderMedecins() {
        ofstream fichier("medecins.csv");
        if (!fichier) {
            cout << "\nErreur: Impossible de creer le fichier medecins.csv" << endl;
            return;
        }


        fichier << "ID,Nom,Prenom,Date_Naissance,Sexe,Email,Date_Embauche,Salaire,Specialite" << endl;


        for (int i = 0; i < nbMedecins; i++) {
            fichier << medecins[i].getId() << ","
                    << medecins[i].getNom() << ","
                    << medecins[i].getPrenom() << ","
                    << medecins[i].getDateNaissance() << ","
                    << medecins[i].getSexe() << ","
                    << medecins[i].getEmail() << ","
                    << medecins[i].getDateEmbauche() << ","
                    << medecins[i].getSalaire() << ","
                    << medecins[i].getSpecialite() << endl;
        }

        fichier.close();
        cout << "\n✓ " << nbMedecins << " medecins sauvegardes dans medecins.csv" << endl;
    }

    void sauvegarderRendezvous() {
        ofstream fichier("rendezvous.csv");
        if (!fichier) {
            cout << "\nErreur: Impossible de creer le fichier rendezvous.csv" << endl;
            return;
        }


        fichier << "ID_RDV,Date,Heure,Motif" << endl;


        for (int i = 0; i < nbRendezvous; i++) {
            fichier << rendezvous[i].getId() << ","
                    << rendezvous[i].getDate() << ","
                    << rendezvous[i].getHeure() << ","
                    << rendezvous[i].getMotif() << endl;
        }

        fichier.close();
        cout << "\n✓ " << nbRendezvous << " rendez-vous sauvegardes dans rendezvous.csv" << endl;
    }

    void sauvegarderAdmissions() {
        ofstream fichier("admissions.csv");
        if (!fichier) {
            cout << "\nErreur: Impossible de creer le fichier admissions.csv" << endl;
            return;
        }


        fichier << "ID_Admission,Date,Etat_Patient,ID_Lit" << endl;


        for (int i = 0; i < nbAdmissions; i++) {
            fichier << admissions[i].getId() << ","
                    << admissions[i].getDate() << ","
                    << admissions[i].getEtat() << ","
                    << admissions[i].getIdLit() << endl;
        }

        fichier.close();
        cout << "\n✓ " << nbAdmissions << " admissions sauvegardees dans admissions.csv" << endl;
    }

    void sauvegarderEquipements() {
        ofstream fichier("equipements.csv");
        if (!fichier) {
            cout << "\nErreur: Impossible de creer le fichier equipements.csv" << endl;
            return;
        }


        fichier << "ID,Nom,Type,Etat" << endl;


        for (int i = 0; i < nbEquipements; i++) {
            fichier << equipements[i].getId() << ","
                    << equipements[i].getNom() << ","
                    << equipements[i].getType() << ","
                    << equipements[i].getEtat() << endl;
        }

        fichier.close();
        cout << "\n✓ " << nbEquipements << " equipements sauvegardes dans equipements.csv" << endl;
    }

    void sauvegarderPrescriptions() {
        ofstream fichier("prescriptions.csv");
        if (!fichier) {
            cout << "\nErreur: Impossible de creer le fichier prescriptions.csv" << endl;
            return;
        }


        fichier << "ID,Date,Details" << endl;


        for (int i = 0; i < nbPrescriptions; i++) {
            fichier << prescriptions[i].getId() << ","
                    << prescriptions[i].getDate() << ","
                    << prescriptions[i].getDetails() << endl;
        }

        fichier.close();
        cout << "\n✓ " << nbPrescriptions << " prescriptions sauvegardees dans prescriptions.csv" << endl;
    }

    void sauvegarderMedicaments() {
        ofstream fichier("medicaments.csv");
        if (!fichier) {
            cout << "\nErreur: Impossible de creer le fichier medicaments.csv" << endl;
            return;
        }


        fichier << "ID,Nom,Posologie" << endl;


        for (int i = 0; i < nbMedicaments; i++) {
            fichier << medicaments[i].getId() << ","
                    << medicaments[i].getNom() << ","
                    << medicaments[i].getPosologie() << endl;
        }

        fichier.close();
        cout << "\n✓ " << nbMedicaments << " medicaments sauvegardes dans medicaments.csv" << endl;
    }

    void sauvegarderTout() {
        cout << "\n=== Sauvegarde de toutes les donnees ===" << endl;
        sauvegarderPatients();
        sauvegarderMedecins();
        sauvegarderRendezvous();
        sauvegarderAdmissions();
        sauvegarderEquipements();
        sauvegarderPrescriptions();
        sauvegarderMedicaments();
        cout << "\n✓ Toutes les donnees ont ete sauvegardees!" << endl;
    }

    //CHARGEMENT CSV

    void chargerPatients() {
        ifstream fichier("patients.csv");
        if (!fichier) {
            cout << "\nAucun fichier patients.csv trouve." << endl;
            return;
        }

        string ligne;
        getline(fichier, ligne);

        nbPatients = 0;
        while (getline(fichier, ligne) && nbPatients < MAX_PATIENTS) {
            stringstream ss(ligne);
            string id_str, nom, prenom, cin, id_dossier_str;

            getline(ss, id_str, ',');
            getline(ss, nom, ',');
            getline(ss, prenom, ',');
            getline(ss, cin, ',');
            getline(ss, id_dossier_str, ',');

            if (!id_str.empty()) {
                int id = stoi(id_str);
                int id_dossier = stoi(id_dossier_str);
                patients[nbPatients] = Patient(id, nom, prenom, cin, id_dossier);
                nbPatients++;
            }
        }

        fichier.close();
        cout << "\n✓ " << nbPatients << " patients charges depuis patients.csv" << endl;
    }

    void chargerMedecins() {
        ifstream fichier("medecins.csv");
        if (!fichier) {
            cout << "\nAucun fichier medecins.csv trouve." << endl;
            return;
        }

        string ligne;
        getline(fichier, ligne);

        nbMedecins = 0;
        while (getline(fichier, ligne) && nbMedecins < MAX_MEDECINS) {
            stringstream ss(ligne);
            string id_str, nom, prenom, date_N, sexe_str, email, date_E, salaire_str, specialite;

            getline(ss, id_str, ',');
            getline(ss, nom, ',');
            getline(ss, prenom, ',');
            getline(ss, date_N, ',');
            getline(ss, sexe_str, ',');
            getline(ss, email, ',');
            getline(ss, date_E, ',');
            getline(ss, salaire_str, ',');
            getline(ss, specialite, ',');

            if (!id_str.empty()) {
                int id = stoi(id_str);
                bool sexe = (sexe_str == "1");
                double salaire = stod(salaire_str);
                medecins[nbMedecins] = Medecin(id, nom, prenom, date_N, sexe, email, date_E, salaire, specialite);
                nbMedecins++;
            }
        }

        fichier.close();
        cout << "\n✓ " << nbMedecins << " medecins charges depuis medecins.csv" << endl;
    }

    void chargerRendezvous() {
        ifstream fichier("rendezvous.csv");
        if (!fichier) {
            cout << "\nAucun fichier rendezvous.csv trouve." << endl;
            return;
        }

        string ligne;
        getline(fichier, ligne);

        nbRendezvous = 0;
        while (getline(fichier, ligne) && nbRendezvous < MAX_RENDEZVOUS) {
            stringstream ss(ligne);
            string id_str, date, heure, motif;

            getline(ss, id_str, ',');
            getline(ss, date, ',');
            getline(ss, heure, ',');
            getline(ss, motif, ',');

            if (!id_str.empty()) {
                int id = stoi(id_str);
                rendezvous[nbRendezvous] = Rendezvous(id, date, heure, motif);
                nbRendezvous++;
            }
        }

        fichier.close();
        cout << "\n✓ " << nbRendezvous << " rendez-vous charges depuis rendezvous.csv" << endl;
    }

    void chargerAdmissions() {
        ifstream fichier("admissions.csv");
        if (!fichier) {
            cout << "\nAucun fichier admissions.csv trouve." << endl;
            return;
        }

        string ligne;
        getline(fichier, ligne);

        nbAdmissions = 0;
        while (getline(fichier, ligne) && nbAdmissions < MAX_ADMISSIONS) {
            stringstream ss(ligne);
            string id_str, date, etat, id_lit_str;

            getline(ss, id_str, ',');
            getline(ss, date, ',');
            getline(ss, etat, ',');
            getline(ss, id_lit_str, ',');

            if (!id_str.empty()) {
                int id = stoi(id_str);
                int id_lit = stoi(id_lit_str);
                admissions[nbAdmissions] = Admission(id, date, etat, id_lit);
                nbAdmissions++;
            }
        }

        fichier.close();
        cout << "\n✓ " << nbAdmissions << " admissions chargees depuis admissions.csv" << endl;
    }

    void chargerEquipements() {
        ifstream fichier("equipements.csv");
        if (!fichier) {
            cout << "\nAucun fichier equipements.csv trouve." << endl;
            return;
        }

        string ligne;
        getline(fichier, ligne);

        nbEquipements = 0;
        while (getline(fichier, ligne) && nbEquipements < MAX_EQUIPEMENTS) {
            stringstream ss(ligne);
            string id_str, nom, type, etat_str;

            getline(ss, id_str, ',');
            getline(ss, nom, ',');
            getline(ss, type, ',');
            getline(ss, etat_str, ',');

            if (!id_str.empty()) {
                int id = stoi(id_str);
                int etat = stoi(etat_str);
                equipements[nbEquipements] = Equipement(id, nom, type, etat);
                nbEquipements++;
            }
        }

        fichier.close();
        cout << "\n✓ " << nbEquipements << " equipements charges depuis equipements.csv" << endl;
    }

    void chargerPrescriptions() {
        ifstream fichier("prescriptions.csv");
        if (!fichier) {
            cout << "\nAucun fichier prescriptions.csv trouve." << endl;
            return;
        }

        string ligne;
        getline(fichier, ligne);

        nbPrescriptions = 0;
        while (getline(fichier, ligne) && nbPrescriptions < MAX_PRESCRIPTIONS) {
            stringstream ss(ligne);
            string id_str, date, details;

            getline(ss, id_str, ',');
            getline(ss, date, ',');
            getline(ss, details);

            if (!id_str.empty()) {
                int id = stoi(id_str);
                prescriptions[nbPrescriptions] = Prescription(id, date, details);
                nbPrescriptions++;
            }
        }

        fichier.close();
        cout << "\n✓ " << nbPrescriptions << " prescriptions chargees depuis prescriptions.csv" << endl;
    }

    void chargerMedicaments() {
        ifstream fichier("medicaments.csv");
        if (!fichier) {
            cout << "\nAucun fichier medicaments.csv trouve." << endl;
            return;
        }

        string ligne;
        getline(fichier, ligne);

        nbMedicaments = 0;
        while (getline(fichier, ligne) && nbMedicaments < MAX_MEDICAMENTS) {
            stringstream ss(ligne);
            string id_str, nom, posologie;

            getline(ss, id_str, ',');
            getline(ss, nom, ',');
            getline(ss, posologie);

            if (!id_str.empty()) {
                int id = stoi(id_str);
                medicaments[nbMedicaments] = Medicament(id, nom, posologie);
                nbMedicaments++;
            }
        }

        fichier.close();
        cout << "\n✓ " << nbMedicaments << " medicaments charges depuis medicaments.csv" << endl;
    }

    void chargerTout() {
        cout << "\n=== Chargement de toutes les donnees ===" << endl;
        chargerPatients();
        chargerMedecins();
        chargerRendezvous();
        chargerAdmissions();
        chargerEquipements();
        chargerPrescriptions();
        chargerMedicaments();
        cout << "\n✓ Toutes les donnees ont ete chargees!" << endl;
    }

    void menuPrincipal() {
        int choix;
        do {
            cout << "\n";
            cout << ".................................................." << endl;
            cout << ".   SYSTEME DE GESTION HOSPITALIERE             ." << endl;
            cout << ".................................................." << endl;
            cout << ".  1. Gestion des Patients                      ." << endl;
            cout << ".  2. Gestion des Medecins                      ." << endl;
            cout << ".  3. Gestion des Rendez-vous                   ." << endl;
            cout << ".  4. Gestion des Admissions                    ." << endl;
            cout << ".  5. Gestion des Equipements                   ." << endl;
            cout << ".  6. Gestion des Prescriptions                 ." << endl;
            cout << ".  7. Gestion des Medicaments                   ." << endl;
            cout << ".  8. Rechercher un Patient                     ." << endl;
            cout << ".  9. Afficher les Statistiques                 ." << endl;
            cout << ". 10. Sauvegarder toutes les donnees (CSV)      ." << endl;
            cout << ". 11. Charger toutes les donnees (CSV)          ." << endl;
            cout << ". 12. Menu Sauvegarde/Chargement                ." << endl;
            cout << ".  0. Quitter                                   ." << endl;
            cout << ".................................................." << endl;
            cout << "Votre choix: ";
            cin >> choix;

            switch(choix) {
                case 1: menuPatients(); break;
                case 2: menuMedecins(); break;
                case 3: menuRendezvous(); break;
                case 4: menuAdmissions(); break;
                case 5: menuEquipements(); break;
                case 6: menuPrescriptions(); break;
                case 7: menuMedicaments(); break;
                case 8: rechercherPatientParId(); break;
                case 9: afficherStatistiques(); break;
                case 10: sauvegarderTout(); break;
                case 11: chargerTout(); break;
                case 12: menuSauvegardeChargement(); break;
                case 0:
                    cout << "\nVoulez-vous sauvegarder avant de quitter? (1=Oui, 0=Non): ";
                    int save;
                    cin >> save;
                    if (save == 1) sauvegarderTout();
                    cout << "\nMerci d'avoir utilise le systeme!\n";
                    break;
                default: cout << "\nChoix invalide!\n";
            }
        } while(choix != 0);
    }

private:
    void menuSauvegardeChargement() {
        int choix;
        do {
            cout << "\n.................................................." << endl;
            cout << ".        MENU SAUVEGARDE / CHARGEMENT           ." << endl;
            cout << ".................................................." << endl;
            cout << ". SAUVEGARDE:                                   ." << endl;
            cout << ".  1. Sauvegarder les Patients                  ." << endl;
            cout << ".  2. Sauvegarder les Medecins                  ." << endl;
            cout << ".  3. Sauvegarder les Rendez-vous               ." << endl;
            cout << ".  4. Sauvegarder les Admissions                ." << endl;
            cout << ".  5. Sauvegarder les Equipements               ." << endl;
            cout << ".  6. Sauvegarder les Prescriptions             ." << endl;
            cout << ".  7. Sauvegarder les Medicaments               ." << endl;
            cout << ".  8. Sauvegarder TOUT                          ." << endl;
            cout << ".                                               ." << endl;
            cout << ". CHARGEMENT:                                   ." << endl;
            cout << ". 11. Charger les Patients                      ." << endl;
            cout << ". 12. Charger les Medecins                      ." << endl;
            cout << ". 13. Charger les Rendez-vous                   ." << endl;
            cout << ". 14. Charger les Admissions                    ." << endl;
            cout << ". 15. Charger les Equipements                   ." << endl;
            cout << ". 16. Charger les Prescriptions                 ." << endl;
            cout << ". 17. Charger les Medicaments                   ." << endl;
            cout << ". 18. Charger TOUT                              ." << endl;
            cout << ".                                               ." << endl;
            cout << ".  0. Retour au menu principal                  ." << endl;
            cout << ".................................................." << endl;
            cout << "Votre choix: ";
            cin >> choix;

            switch(choix) {
                case 1: sauvegarderPatients(); break;
                case 2: sauvegarderMedecins(); break;
                case 3: sauvegarderRendezvous(); break;
                case 4: sauvegarderAdmissions(); break;
                case 5: sauvegarderEquipements(); break;
                case 6: sauvegarderPrescriptions(); break;
                case 7: sauvegarderMedicaments(); break;
                case 8: sauvegarderTout(); break;

                case 11: chargerPatients(); break;
                case 12: chargerMedecins(); break;
                case 13: chargerRendezvous(); break;
                case 14: chargerAdmissions(); break;
                case 15: chargerEquipements(); break;
                case 16: chargerPrescriptions(); break;
                case 17: chargerMedicaments(); break;
                case 18: chargerTout(); break;

                case 0: break;
                default: cout << "\nChoix invalide!\n";
            }
        } while(choix != 0);
    }

    void menuPatients() {
        int choix;
        cout << "\n--- Menu Patients ---" << endl;
        cout << "1. Ajouter un patient" << endl;
        cout << "2. Afficher tous les patients" << endl;
        cout << "Votre choix: ";
        cin >> choix;

        if (choix == 1) ajouterPatient();
        else if (choix == 2) afficherPatients();
    }

    void menuMedecins() {
        int choix;
        cout << "\n--- Menu Medecins ---" << endl;
        cout << "1. Ajouter un medecin" << endl;
        cout << "2. Afficher tous les medecins" << endl;
        cout << "Votre choix: ";
        cin >> choix;

        if (choix == 1) ajouterMedecin();
        else if (choix == 2) afficherMedecins();
    }

    void menuRendezvous() {
        int choix;
        cout << "\n--- Menu Rendez-vous ---" << endl;
        cout << "1. Ajouter un rendez-vous" << endl;
        cout << "2. Afficher tous les rendez-vous" << endl;
        cout << "Votre choix: ";
        cin >> choix;

        if (choix == 1) ajouterRendezvous();
        else if (choix == 2) afficherRendezvous();
    }

    void menuAdmissions() {
        int choix;
        cout << "\n--- Menu Admissions ---" << endl;
        cout << "1. Ajouter une admission" << endl;
        cout << "2. Afficher toutes les admissions" << endl;
        cout << "Votre choix: ";
        cin >> choix;

        if (choix == 1) ajouterAdmission();
        else if (choix == 2) afficherAdmissions();
    }

    void menuEquipements() {
        int choix;
        cout << "\n--- Menu Equipements ---" << endl;
        cout << "1. Ajouter un equipement" << endl;
        cout << "2. Afficher tous les equipements" << endl;
        cout << "Votre choix: ";
        cin >> choix;

        if (choix == 1) ajouterEquipement();
        else if (choix == 2) afficherEquipements();
    }

    void menuPrescriptions() {
        int choix;
        cout << "\n--- Menu Prescriptions ---" << endl;
        cout << "1. Ajouter une prescription" << endl;
        cout << "2. Afficher toutes les prescriptions" << endl;
        cout << "Votre choix: ";
        cin >> choix;

        if (choix == 1) ajouterPrescription();
        else if (choix == 2) afficherPrescriptions();
    }

    void menuMedicaments() {
        int choix;
        cout << "\n--- Menu Medicaments ---" << endl;
        cout << "1. Ajouter un medicament" << endl;
        cout << "2. Afficher tous les medicaments" << endl;
        cout << "Votre choix: ";
        cin >> choix;

        if (choix == 1) ajouterMedicament();
        else if (choix == 2) afficherMedicaments();
    }
};



int main() {
    SystemeGestionHospital systeme;
    systeme.menuPrincipal();
    return 0;
}
