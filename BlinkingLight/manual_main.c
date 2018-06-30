int main(void)
{
    // configure button
    GPIOA->CRL |= GPIO_CRL_CNF0_0;

    // configure led 
    GPIOC->CRH = GPIO_CRH_MODE8_1;
    
    while (1)
    {
        uint16_t button = GPIOA->IDR;

        if ((button & (1<<0)) == (1<<0)){
            // led = on
            GPIOC->BSRR |= (1<<8);
        } else {
            // led = off
            GPIOC->BRR |= (1<<8);
        }
    }
}
