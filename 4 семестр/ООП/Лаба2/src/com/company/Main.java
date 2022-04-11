package com.company;

public class Main {

    public static void main(String[] args) {
        SailingVessel sailingVessel = new SailingVessel("Крузенштерн", 5000, "Россия",
                150, 3);
        Corvette corvette = new Corvette("Виктория", 4000, "Великобритания",
                100, "Пушки");
	    Steamer steamer = new Steamer("Аврора", 6730, "Россия", 300,
                5000, 5);
	    Dock dock = new Dock();

	    sailingVessel.sail(500);
        sailingVessel.sail(2000);
        sailingVessel.sail(100);

        System.out.println();

        steamer.sail(900);
        steamer.sail(300);
        steamer.sail(100);

        System.out.println();

        dock.refuel(steamer);
        dock.repair(sailingVessel);

        System.out.println();

        sailingVessel.sail(300);
        steamer.sail(300);

        System.out.println();

        sailingVessel.showInfo();
        corvette.showInfo();
        steamer.showInfo("info.txt");

        System.out.println();

        System.out.println(Vessel.getVesselsList());
    }
}
