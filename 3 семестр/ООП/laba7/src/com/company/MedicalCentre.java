package com.company;

public class MedicalCentre extends OlympicConstruction {

    public MedicalCentre(int number, String name) {
        super(number, name);
    }

    @Override
    void check() {
        System.out.println("Название медицинского центра – " + this.getNAME());
    }
}
