package com.company;

import java.util.Arrays;
import java.util.Scanner;

public class Main {

    public static void assignPatient(Hospital h, Patient p) {
        for (Ward w: h.getWardList()) {
            if (w.addPatient(p))
                return;
        }
        System.out.println("Больница переполнена!");
    }

    public static void main(String[] args) {
        Scanner input = new Scanner(System.in);

        Hospital hospital = new Hospital();

        while (true) {
            System.out.println("Введите ваш выбор:\n" +
                    "1. Записать пациента;\n" +
                    "2. Добавить новую палату;\n" +
                    "3. Вывести информацию о палатах;\n" +
                    "4. Определить пациентов в карантин;\n" +
                    "5. Выход.");
            String choice = input.nextLine();

            switch (choice) {
                case ("1") -> {
                    System.out.println("Введите имя пациента:");
                    String patientName = input.nextLine();
                    Patient newPatient = new Patient(patientName);

                    assignPatient(hospital, newPatient);
                }

                case ("2") -> {
                    hospital.addWard();
                    Ward newWard =  hospital.getWardList().get(hospital.getWardList().size() - 1);
                    System.out.printf("Открыта палата номер %d\n", newWard.getNUMBER());
                }

                case ("3") -> {
                    for (Ward w: hospital.getWardList()) {
                        System.out.printf("Палата %d:\n", w.getNUMBER());
                        for (Patient p: w.getPatientList()) {
                            System.out.printf("%s: %s, %.1f\n", p.getNAME(), Arrays.toString(p.getTEMPERATURE()),
                                    p.getAVERAGE_TEMPERATURE());
                        }
                    }

                    if (hospital.getQuarantineList().size() == 0)
                        System.out.println("Пациентов на карантине нет.");
                    else
                        for (Patient p: hospital.getQuarantineList())
                            System.out.printf("%s: %.1f\n", p.getNAME(), p.getAVERAGE_TEMPERATURE());
                }

                case ("4") -> {
                    int patientsBeforeQuarantine = hospital.getQuarantineList().size();
                    hospital.addQuarantineList();
                    int patientsAfterQuarantine = hospital.getQuarantineList().size();
                    System.out.printf("Было помещено в карантин %d больных.\n",
                            patientsAfterQuarantine - patientsBeforeQuarantine);
                }

                case ("5") ->
                    System.exit(0);

                default ->
                    System.out.println("Введите значение от 1 до 5!");
            }
        }
    }
}
