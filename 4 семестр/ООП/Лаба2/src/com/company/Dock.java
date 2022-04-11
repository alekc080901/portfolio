package com.company;

public class Dock {
    public void repair(Vessel vessel) {
        vessel.setDurability(vessel.getMAX_DURABILITY());
        System.out.printf("Судно %s починено.\n", vessel.getNAME());
    }

    public void refuel(Steamer steamer) {
        steamer.setFuelRemaining(steamer.getMAX_FUEL_AMOUNT());
        System.out.printf("Пароход %s заправлен.\n", steamer.getNAME());
    }
}
