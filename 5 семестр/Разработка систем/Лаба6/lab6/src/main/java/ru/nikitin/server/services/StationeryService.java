package ru.nikitin.server.services;

import ru.nikitin.server.entities.Stationery;

import java.util.List;

public interface StationeryService {
    boolean add(Stationery stationery);
    boolean delete(Integer id);
    boolean update(Integer id, Stationery stationery);
    List<Stationery> getByManufacturer(String manufacturer);
    List<Stationery> getAll();
}
