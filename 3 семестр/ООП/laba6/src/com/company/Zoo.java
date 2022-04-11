package com.company;

import java.util.ArrayList;
import java.util.Arrays;

public class Zoo {
    private final ArrayList<WishingZoo> livingBeings = new ArrayList<>();
    private final ArrayList<Aviary> aviaries = new ArrayList<>();
    private final ArrayList<WishingZoo> beingsNotInZoo = new ArrayList<>();

    private static int aviaryCount = 1;

    public void addLivingBeings(WishingZoo... beings) {
        livingBeings.addAll(Arrays.asList(beings));
    }

    public void addAviary(Aviary aviary) {
        aviaries.add(aviary);
    }

    private ArrayList<Integer> getAviaryNumbers() {
        ArrayList<Integer> numbers = new ArrayList<>();
        for (Aviary aviary: aviaries)
            numbers.add(aviary.getNUMBER());

        return numbers;
    }

    private ArrayList<Aviary> getColdAviaries() {
        ArrayList<Aviary> coldAviaries = new ArrayList<>();

        for (Aviary aviary: aviaries)
            if (aviary.getClass() == ColdAviary.class)
                coldAviaries.add(aviary);

        return  coldAviaries;
    }

    private ArrayList<Aviary> getHeatAviaries() {
        ArrayList<Aviary> heatAviaries = new ArrayList<>();

        for (Aviary aviary: aviaries)
            if (aviary.getClass() == HeatAviary.class)
                heatAviaries.add(aviary);

        return  heatAviaries;
    }

    private Aviary findEmptyAviary(ArrayList<Aviary> list) {

        for (Aviary aviary: list)
            if (aviary.getBeing() == null)
                return aviary;

        return null;
    }

    public void distribution() {
        Aviary aviary;

        for (WishingZoo being: livingBeings) {

            if (being instanceof Exotic) {
                boolean isColdLoving = being instanceof Coldloving;

                // Проверка на повторение номера вольера
                while (getAviaryNumbers().contains(aviaryCount)) {
                    aviaryCount++;
                }

                // Определение, какой вольер занимать животному
                ColdAviary emptyColdAviary = (ColdAviary) findEmptyAviary(getColdAviaries());
                HeatAviary emptyHeatAviary = (HeatAviary) findEmptyAviary(getHeatAviaries());
                if (isColdLoving && emptyColdAviary != null) {
                    aviaries.remove(emptyColdAviary);
                    aviary = emptyColdAviary;
                }
                else if (!isColdLoving && emptyHeatAviary != null) {
                    aviaries.remove(emptyHeatAviary);
                    aviary = emptyHeatAviary;
                }
                else
                    aviary = (isColdLoving) ? new ColdAviary(aviaryCount) : new HeatAviary(aviaryCount);

                aviary.occupyAviary( (Exotic) being);
                System.out.printf("Животное %s было заселено в вольер %d\n", being, aviary.getNUMBER());
                aviaries.add(aviary);
                aviaryCount++;
            }
            else
                beingsNotInZoo.add(being);
        }

        livingBeings.clear();
    }


    public void display() {
        System.out.printf("Количество холодных вольеров: %d;\n" +
                          "Количество теплых вольеров: %d.\n\n",
                           getColdAviaries().size(), getHeatAviaries().size());

        System.out.println("Список вольеров:");
        for (Aviary aviary: aviaries)
            System.out.println(aviary);

        System.out.println("\nОтвергнутые животные:");
        for (WishingZoo being: beingsNotInZoo)
            System.out.println(being);
    }

}
