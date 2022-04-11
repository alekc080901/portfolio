package com.company;

import java.util.ArrayList;

public class Hospital {
    private final ArrayList<Ward> wardList = new ArrayList<Ward>();
    private final ArrayList<Patient> quarantineList = new ArrayList<Patient>();
    private int wardNumber = 1;

    public Hospital() {
        addWard();
        addWard();
    }

    public void addWard() {
        wardList.add(new Ward(wardNumber));
        wardNumber++;
    }

    public void addPatient(Patient p) {
        quarantineList.add(p);
    }

    public void addQuarantineList() {
        for (Ward ward: wardList) {
            ArrayList<Patient> patients = ward.getPatientList();
            for (int i = 0; i < patients.size(); i++){
                if (patients.get(i).getAVERAGE_TEMPERATURE() >= 37.6) {
                    addPatient(patients.get(i));
                    ward.delPatient(patients.get(i));
                    i--;
                }
            }
        }
    }

    public ArrayList<Ward> getWardList() {
        return wardList;
    }

    public ArrayList<Patient> getQuarantineList() {
        return quarantineList;
    }
}
