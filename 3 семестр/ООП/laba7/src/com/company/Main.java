package com.company;

public class Main {

    public static void main(String[] args) {

        // Объявление экземпляров зданий
        Hostel hostel1 = new Hostel(1, "Общежитие1");
        Hostel hostel2 = new Hostel(2, "Общежитие2");
        Library library = new Library(1, "Библиотека");
        MedicalCentre medicalCentre = new MedicalCentre(1, "Медицинский центр");
        OlympicStadium olympicStadium = new OlympicStadium(1, "Стадион");
        ConcertHall concertHall = new ConcertHall(1, "Концертный зал");

        University university = new University("ИКИТ");
        university.addConstructions(hostel1, hostel2, library, medicalCentre, olympicStadium, concertHall);
        university.showInfo();

        // Переписанные функции абстрактных классов
        hostel1.repair();
        library.repair();

        System.out.println();

        medicalCentre.check();
        olympicStadium.check();
        concertHall.check();

        System.out.println();

        // Аренда зданий
        RentalDepartment<RentObject> rentalDepartment = new RentalDepartment<>();

        rentalDepartment.registerNewBuildings(hostel1, hostel2, olympicStadium, concertHall);
        rentalDepartment.findByCost(">1000").forEach(building ->
                System.out.printf("Название: %s. Цена: %d\n",building.getNAME(), building.getPrice()));

        System.out.println();

        rentalDepartment.rentBuilding(olympicStadium);

        System.out.println();

        rentalDepartment.showInfo();

        System.out.println();

        rentalDepartment.freeBuilding(olympicStadium);
        rentalDepartment.deleteBuilding(concertHall);
        rentalDepartment.rentBuilding(hostel1);

        System.out.println();
        rentalDepartment.showInfo();
    }
}
