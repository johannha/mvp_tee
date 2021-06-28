# Useful Commands

Compile smart contracts: `truffle compile`

Compile and override: `truffle compile --all `

Run migrations: `truffle migrate` (Ganache running before running migrate)

Run migrations: `truffle develop`

## More information

Migrations are JavaScript files that help you deploy contracts to Eth network.

Deployer object is main interface for staging deployment tasks.

Writing data to Eth network = **transaction** and won't expose return value

Reading data from Eth network = **call**
