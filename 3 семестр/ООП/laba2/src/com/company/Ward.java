package com.company;

import java.util.ArrayList;

public class Ward {
    private final int NUMBER;
    private final ArrayList<Patient> patientList = new ArrayList<>();

    public Ward(int number) {
        this.NUMBER = number;
    }

    public boolean addPatient(Patient p) {
        if (patientList.size() < 4) {
            patientList.add(p);
            return  true;
        }
        return false;
    }

    public void delPatient(Patient p) {
        patientList.remove(p);
    }

    public ArrayList<Patient> getPatientList() {
        return patientList;
    }

    public int getNUMBER() {
        return NUMBER;
    }
}
