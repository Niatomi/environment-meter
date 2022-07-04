package ru.niatomi.controller.Impl;

import io.swagger.v3.oas.annotations.parameters.RequestBody;
import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RestController;
import ru.niatomi.controller.ClientController;
import ru.niatomi.model.domain.arduinoConfig.ReferenceData;
import ru.niatomi.model.dto.time.ExactTimeDto;
import ru.niatomi.model.dto.time.TimePlanAndExactDto;
import ru.niatomi.model.dto.time.TimePlanDto;

/**
 * @author niatomi
 */
@RestController
@RequestMapping("/client")
public class ClientControllerImpl implements ClientController {
    @Override
    public ResponseEntity<String> updateReferenceData(ReferenceData referenceData) {
        return null;
    }

    @Override
    public ResponseEntity<String> addExactTime(ExactTimeDto exactTimeDto) {
        return null;
    }

    @Override
    public ResponseEntity<String> addTimePlan(@RequestBody(content = {new TimePlanDto(new Year(1234))}) TimePlanDto timePlanDto) {
        return null;
    }

    @Override
    public ResponseEntity<TimePlanAndExactDto> getAllPlan() {
        return null;
    }
}
