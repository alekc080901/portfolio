package com.company;

import java.io.FileWriter;
import java.io.IOException;

public class Steamer extends Vessel {
    private final int FUEL_CONSUMPTION;
    private final int MAX_FUEL_AMOUNT;

    private int fuelRemaining;
    private boolean inOcean = false;

    public Steamer(String name, int displacement, String stateFlag, int durability,
                   int maxFuelAmount, int fuelConsumption) {
        super(name, displacement, stateFlag, durability);
        this.FUEL_CONSUMPTION = fuelConsumption;
        this.MAX_FUEL_AMOUNT = maxFuelAmount;

        this.fuelRemaining = maxFuelAmount;
    }

    public void estimateRange() {
        System.out.printf("Вы можете проплыть %d км.\n", fuelRemaining / FUEL_CONSUMPTION);
    }

    @Override
    public void sail(int distance) {
        if (inOcean) {
            System.out.println("Корабль еще в океане");
            return;
        }

        super.sail(distance);

        for (int sailed_distance = 0; sailed_distance < distance; sailed_distance++) {
            fuelRemaining = fuelRemaining - FUEL_CONSUMPTION;
            if (fuelRemaining < 0) {
                fuelRemaining = 0;
                System.out.printf("Ваше топливо закончилось, и вы дрейфуете по океану.\n" +
                        "Вы недоплыли %d км.\n", distance - sailed_distance);
                inOcean = true;
                return;
            }
        }

        System.out.printf("Оставшееся топливо: %d/%d\n", fuelRemaining, MAX_FUEL_AMOUNT);
    }

    @Override
    public void showInfo() {
        System.out.printf("Информация о пароходе %s:\nВодоизмещение – %d.\nГосударство – %s.\n" +
                "Текущая прочность  – %d/%d.\nПотребление топлива  – %d.\nОставшееся топливо  – %d/%d.\n\n",
                getNAME(), getDISPLACEMENT(), getSTATE_FLAG(), getDurability(), getMAX_DURABILITY(),
                FUEL_CONSUMPTION, fuelRemaining, MAX_FUEL_AMOUNT);
    }

    @Override
    public void showInfo(String path) {
        try(FileWriter writer = new FileWriter(path, false))
        {
            String text = String.format("Информация о пароходе %s:\nВодоизмещение – %d.\nГосударство – %s.\n" +
                            "Текущая прочность  – %d/%d.\nПотребление топлива  – %d кг/км.\n" +
                            "Оставшееся топливо  – %d/%d кг.",
                    getNAME(), getDISPLACEMENT(), getSTATE_FLAG(), getDurability(), getMAX_DURABILITY(),
                    FUEL_CONSUMPTION, fuelRemaining, MAX_FUEL_AMOUNT);
            writer.write(text);
            writer.flush();
        }
        catch(IOException ex){
            System.out.println(ex.getMessage());
        }
    }

    public void setFuelRemaining(int fuelRemaining) {
        this.fuelRemaining = fuelRemaining;
        if (fuelRemaining > 0)
            inOcean = false;
    }

    public int getMAX_FUEL_AMOUNT() {
        return MAX_FUEL_AMOUNT;
    }
}
