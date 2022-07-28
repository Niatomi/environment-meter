package ru.niatomi.controller.Impl;

import io.swagger.v3.oas.annotations.parameters.RequestBody;
import lombok.RequiredArgsConstructor;
import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RestController;
import ru.niatomi.controller.ClientController;
import ru.niatomi.model.domain.arduinoConfig.ReferenceData;
import ru.niatomi.model.dto.configFiles.ReferenceDataDto;
import ru.niatomi.model.dto.data.DataDto;
import ru.niatomi.model.dto.time.ExactTimeDto;
import ru.niatomi.model.dto.time.TimePlanAndExactDto;
import ru.niatomi.model.dto.time.TimePlanDto;
import ru.niatomi.service.ClientService;

import java.util.List;

/**
 * @author niatomi
 */
@RestController
@RequiredArgsConstructor
@RequestMapping("/client")
public class ClientControllerImpl implements ClientController {

    private final ClientService clientService;

    @Override
    public ResponseEntity<String> updateReferenceData(ReferenceDataDto referenceData) {
        return ResponseEntity.ok(clientService.updateReferenceData(referenceData));
    }

    @Override
    public ResponseEntity<String> addExactTime(ExactTimeDto exactTimeDto) {
        return ResponseEntity.ok(clientService.addExactTime(exactTimeDto));
    }

    @Override
    public ResponseEntity<String> addTimePlan(@RequestBody TimePlanDto timePlanDto) {
        return ResponseEntity.ok(clientService.addTimePlan(timePlanDto));
    }

    @Override
    public ResponseEntity<TimePlanAndExactDto> getAllTime() {
        return ResponseEntity.ok(clientService.getAllTime());
    }

    @Override
    public ResponseEntity<List<DataDto>> getData() {
        return ResponseEntity.ok(clientService.getData());
    }
}
