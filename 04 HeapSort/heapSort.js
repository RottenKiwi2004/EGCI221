function floorDiv(n, d) { return Math.floor(n / d);}

class BinaryHeap {

    constructor(initialArray) {
        this.heap = [null]
        if (initialArray != undefined) {
            this.heap = this.heap.concat(initialArray);
            for(let i = floorDiv(this.heap.length - 1, 2); i >= 1; i--) this.percolateDown(i);
        }
    }

    isEmpty() {
        return this.heap.length === 1;
    }

    insert(number) {
        this.heap.push(number);
        this.percolateUp(this.heap.length - 1);
    }

    findMin() {
        if (this.isEmpty()) return null;
        return this.heap[1];
    }

    deleteMin() {
        if (this.isEmpty()) return null;
        let minElement = this.findMin();
        this.heap[1] = this.heap.pop(); // pop() return last element and remove it from array
        this.percolateDown(1);
        return minElement;
    }

    swap(i, j) {
        let temp = this.heap[i];
        this.heap[i] = this.heap[j];
        this.heap[j] = temp;
    }

    percolateUp(hole) {
        while (hole > 1 && this.heap[hole] < this.heap[floorDiv(hole, 2)]) {
            this.swap(hole, floorDiv(hole, 2));
            hole = floorDiv(hole, 2);
        }
    }

    percolateDown(hole) {
        let currentSize = this.heap.length - 1;
        while (hole * 2 <= currentSize) {
            let child = hole * 2;
            if (child != currentSize && this.heap[child + 1] < this.heap[child]) child++;
            if (this.heap[child] < this.heap[hole]) this.swap(hole, child);
            else break;
            hole = child;
        }
    }

    print() {
        console.log(this.heap);
    }

}

// const heap = new BinaryHeap();
// heap.print();

const heap1 = new BinaryHeap([9, 1, 2, 3, 5, 7]);
heap1.print();


const heap2 = new BinaryHeap();
for(let i=0; i<100; i++) heap2.insert(Math.random());
heap2.print();

sorted = []
for(let i=0; i<100; i++) sorted.push(heap2.deleteMin());
console.log(sorted);
