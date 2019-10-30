var Field = function () {

    this.xPosition = 0;
    this.yPosition = 0;
    this.mine = false;
    this.minesAround = 0;
    this.neighbours = [];
    this.flagged = false;
    this.uncovered = false;
    this.falseMine = false;

    this.eventDispatcher = new EventDispatcher();

    this.uncover = function () {
        if (!this.uncovered) {

            if (this.flagged) {
                this.addOrRemoveFlag();
            }


            this.uncovered = true;


            if (this.mine) {
                this.eventDispatcher.dispatchEvent('mineUncoveredEvent');
            } else {
                this.eventDispatcher.dispatchEvent('fieldUncoveredEvent');
            }
        }
    };


    this.addOrRemoveFlag = function () {
        if (!this.uncovered) {
            this.eventDispatcher.dispatchEvent('addOrRemoveFlagEvent');
            this.flagged = !this.flagged;
        }
    };

};