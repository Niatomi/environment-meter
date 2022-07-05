package ru.niatomi.model.domain.validation.validatior;

import ru.niatomi.model.domain.validation.I2CCheckTimeRestrictions;

import javax.validation.ConstraintValidator;
import javax.validation.ConstraintValidatorContext;

/**
 * @author niatomi
 */
public class I2CCheckTimeRestrictionsValidator implements ConstraintValidator<I2CCheckTimeRestrictions, Long> {


    @Override
    public void initialize(I2CCheckTimeRestrictions constraintAnnotation) {
        ConstraintValidator.super.initialize(constraintAnnotation);
    }

    @Override
    public boolean isValid(Long value, ConstraintValidatorContext context) {
        return value != null && (value > 40);
    }
}
