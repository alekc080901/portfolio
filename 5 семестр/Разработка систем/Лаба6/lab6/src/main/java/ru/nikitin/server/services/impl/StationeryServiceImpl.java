package ru.nikitin.server.services.impl;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.data.domain.Sort;
import org.springframework.stereotype.Service;
import ru.nikitin.server.services.StationeryService;
import ru.nikitin.server.entities.Stationery;
import ru.nikitin.server.repos.StationeryRepository;

import java.util.List;

@Service
public class StationeryServiceImpl implements StationeryService {
    @Autowired
    private StationeryRepository stationeryRepository;

    @Override
    public boolean add(Stationery stationery) {
        this.stationeryRepository.save(stationery);
        return true;
    }

    @Override
    public boolean delete(Integer id) {
        if (checkId(id)) {
            this.stationeryRepository.deleteById(id);
            return true;
        }
        return false;
    }

    @Override
    public boolean update(Integer id, Stationery stationery) {
        if (checkId(id)) {
            this.stationeryRepository.deleteById(id);
            this.stationeryRepository.save(stationery);
            return true;
        }
        return false;
    }

    @Override
    public List<Stationery> getByManufacturer(String manufacturer) {
        return this.stationeryRepository.findStationeryByManufacturer(manufacturer);
    }
    @Override
    public List<Stationery> getAll() {
        return this.stationeryRepository.findAll(Sort.by("type"));
    }

    private boolean checkId(int id) {
        return this.stationeryRepository.findById(id).isPresent();
    }

}
