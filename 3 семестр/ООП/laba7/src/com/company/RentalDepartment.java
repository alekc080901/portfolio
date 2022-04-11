package com.company;

import java.util.ArrayList;
import java.util.Collections;
import java.util.List;
import java.util.stream.Collectors;

public class RentalDepartment<T extends RentObject> {

    private final List<T> freeBuildings = new ArrayList<>();
    private final List<T> rentedBuildings = new ArrayList<>();

    @SafeVarargs
    public final void registerNewBuildings(T... buildings) {
        Collections.addAll(freeBuildings, buildings);
    }

    public void deleteBuilding(T building) {
        freeBuildings.remove(building);
        rentedBuildings.remove(building);
    }

    public void rentBuilding(T building) {
        if (!freeBuildings.contains(building)) {
            System.out.println("Данная постройка не зарегистрирована!");
            return;
        }

        freeBuildings.remove(building);
        building.rent();
        rentedBuildings.add(building);
    }

    public void freeBuilding(T building) {
        if (!rentedBuildings.contains(building)) {
            System.out.println("Данная постройка не зарегистрирована!");
            return;
        }

        freeBuildings.add(building);
        rentedBuildings.remove(building);
    }

    public List<T> findByCost(String condition) {
        int value;
        try {
            value = Integer.parseInt(condition.substring(1));
        } catch (NumberFormatException e) {
            System.out.println("Условие введено неправильно!");
            return null;
        }

        switch (condition.charAt(0)) {
            case ('<'):
                return freeBuildings.stream()
                        .filter(building -> building.getPrice() < value).collect(Collectors.toList());

            case ('>'):
                return freeBuildings.stream()
                        .filter(building -> building.getPrice() > value).collect(Collectors.toList());

            case ('='):
                return freeBuildings.stream()
                        .filter(building -> building.getPrice() == value).collect(Collectors.toList());

            default:
                System.out.println("Условие введено неправильно!");
                return null;
        }

    }

    public void showInfo() {
        System.out.println("Арендованные здания:");
        rentedBuildings.forEach(building ->
                System.out.printf("Название: %s. Цена: %d\n",building.getNAME(), building.getPrice()));

        System.out.println("Свободные здания:");
        freeBuildings.forEach(building ->
                System.out.printf("Название: %s. Цена: %d\n",building.getNAME(), building.getPrice()));
    }
}
