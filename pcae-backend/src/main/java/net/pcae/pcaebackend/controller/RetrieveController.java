package net.pcae.pcaebackend.controller;

import net.pcae.pcaebackend.dto.BetweenDto;
import net.pcae.pcaebackend.model.EntryModel;
import net.pcae.pcaebackend.repository.EntryRepository;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.http.HttpStatus;
import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.*;

import java.util.List;

@RestController
@RequestMapping("retrieve")
public class RetrieveController {

    @Autowired
    private EntryRepository entryRepository;

    @GetMapping("all")
    public ResponseEntity<List<EntryModel>> getAll() {
        return new ResponseEntity<>(entryRepository.findAll(), HttpStatus.OK);
    }

    @PostMapping("between")
    public ResponseEntity<List<EntryModel>> postBetween(@RequestBody BetweenDto betweenDto) {
        return new ResponseEntity<>(entryRepository.findBetweenPoints(betweenDto.minLat,betweenDto.maxLat,betweenDto.minLon,betweenDto.maxLon), HttpStatus.OK);
    }

}
