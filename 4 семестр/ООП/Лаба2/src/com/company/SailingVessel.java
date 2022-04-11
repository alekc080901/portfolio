package com.company;

import java.io.FileWriter;
import java.io.IOException;

public class SailingVessel extends Vessel {
    private final int SAILS_NUMBER;

    public SailingVessel(String name, int displacement, String stateFlag, int durability, int sailsNumber) {
        super(name, displacement, stateFlag, durability);
        this.SAILS_NUMBER = sailsNumber;
    }

    @Override
    public void showInfo() {
        System.out.printf("Информация о пароходе %s:\nВодоизмещение – %d.\nГосударство – %s.\n" +
                        "Текущая прочность  – %d/%d.\nКоличество парусов – %d.\n\n",
                getNAME(), getDISPLACEMENT(), getSTATE_FLAG(), getDurability(), getMAX_DURABILITY(), SAILS_NUMBER);
    }

    @Override
    public void showInfo(String path) {
        try(FileWriter writer = new FileWriter(path, false))
        {
            String text = String.format("Информация о пароходе %s:\nВодоизмещение – %d.\nГосударство – %s.\n" +
                            "Текущая прочность  – %d/%d.\nКоличество парусов – %d.\n",
                    getNAME(), getDISPLACEMENT(), getSTATE_FLAG(), getDurability(), getMAX_DURABILITY(), SAILS_NUMBER);
            writer.write(text);
            writer.flush();
        }
        catch(IOException ex){
            System.out.println(ex.getMessage());
        }
    }
}
