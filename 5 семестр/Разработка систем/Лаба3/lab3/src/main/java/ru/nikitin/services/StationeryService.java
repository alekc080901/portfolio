package ru.nikitin.services;

import ru.nikitin.entities.Stationery;

import java.util.List;

public interface StationeryService {
    void add(Stationery stationery);
    boolean delete(Integer id);
    boolean update(Integer id, Stationery stationery);
    List<Stationery> getByManufacturer(String manufacturer);
    List<Stationery> getAll();
}
