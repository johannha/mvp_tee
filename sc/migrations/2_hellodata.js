const hellodata = artifacts.require("Hellodata");

module.exports = function (deployer) {
  deployer.deploy(hellodata);
};
