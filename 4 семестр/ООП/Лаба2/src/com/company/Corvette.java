package com.company;

import java.io.FileWriter;
import java.io.IOException;

public class Corvette extends Vessel {
    private String weaponry;

    public Corvette(String name, int displacement, String stateFlag, int durability, String weaponry) {
        super(name, displacement, stateFlag, durability);
        this.weaponry = weaponry;
    }

    public void setWeaponry(String weaponry) {
        this.weaponry = weaponry;
    }

    @Override
    public void showInfo() {
        System.out.printf("Информация о пароходе %s:\nВодоизмещение – %d.\nГосударство – %s.\n" +
                        "Текущая прочность  – %d/%d.\nВооружение – %s.\n\n",
                getNAME(), getDISPLACEMENT(), getSTATE_FLAG(), getDurability(), getMAX_DURABILITY(), weaponry);
    }

    @Override
    public void showInfo(String path) {
        try(FileWriter writer = new FileWriter(path, false))
        {
            String text = String.format("Информация о пароходе %s:\nВодоизмещение – %d.\nГосударство – %s.\n" +
                            "Текущая прочность  – %d/%d.\nВооружение – %s.\n",
                    getNAME(), getDISPLACEMENT(), getSTATE_FLAG(), getDurability(), getMAX_DURABILITY(), weaponry);
            writer.write(text);
            writer.flush();
        }
        catch(IOException ex){
            System.out.println(ex.getMessage());
        }
    }
}
