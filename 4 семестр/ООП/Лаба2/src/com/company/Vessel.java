package com.company;

import java.util.ArrayList;
import java.util.List;

abstract public class Vessel {
    private final String NAME;
    private final int DISPLACEMENT;
    private final String STATE_FLAG;
    private final int MAX_DURABILITY;
    private int durability;
    private static final List<String> vesselsList = new ArrayList<>();

    public abstract void showInfo();
    public abstract void showInfo(String path);

    public Vessel(String name, int displacement, String stateFlag, int maxDurability) {
        this.NAME = name;
        this.DISPLACEMENT = displacement;
        this.STATE_FLAG = stateFlag;
        this.MAX_DURABILITY = maxDurability;

        this.durability = maxDurability;

        addVessel(this);
    }

    public void sail(int distance) {
        if (durability <= 0) {
            System.out.println("Судно сломано и не может плавать");
            return;
        }

        durability = (int) (durability - Math.round(0.1 * distance));
        if (durability <= 0) {
            durability = 0;
        }

        System.out.printf("Место назначения успешно достигнуто. Прочность судна – %d/%d\n",
                durability, MAX_DURABILITY);
    }

    public static void addVessel(Vessel vessel) {
        vesselsList.add(vessel.NAME);
    }

    public static List<String> getVesselsList() {
        return vesselsList;
    }

    public void setDurability(int durability) {
        this.durability = durability;
    }

    public String getNAME() {
        return NAME;
    }

    public int getDISPLACEMENT() {
        return DISPLACEMENT;
    }

    public String getSTATE_FLAG() {
        return STATE_FLAG;
    }

    public int getDurability() {
        return durability;
    }

    public int getMAX_DURABILITY() {
        return MAX_DURABILITY;
    }
}
