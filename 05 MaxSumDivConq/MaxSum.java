import java.util.Random;

public class MaxSum {

    static int [] maxCross(int [] A, int low, int mid, int high) {

        int maxLeft = mid, maxRight = mid+1;

        int leftSum = Integer.MIN_VALUE;
        int sumLeft = 0;
        for (int i=mid; i >= low; i--) {
            sumLeft += A[i];
            if (sumLeft > leftSum) {
                leftSum = sumLeft;
                maxLeft = i;
            }
        }

        int rightSum = Integer.MIN_VALUE;
        int sumRight = 0;
        for (int i=mid+1; i <= high; i++) {
            sumRight += A[i];
            if (sumRight > rightSum) {
                rightSum = sumRight;
                maxRight = i;
            }
        }

        int [] result = {maxLeft, maxRight, leftSum + rightSum};
        return result;

    }

    static int [] maxSubarray(int [] A, int low, int high) {
        if (high == low) {
            int [] result = {low, high, A[low]}; 
            return result;
        }
        
        int mid = (low + high) / 2;
        int [] leftResult = maxSubarray(A, low, mid);
        int [] rightResult = maxSubarray(A, mid+1, high);
        int [] crossResult = maxCross(A, low, mid, high);

        if (leftResult[2] >= rightResult[2] && leftResult[2] >= crossResult[2])
            return leftResult;
        if (rightResult[2] >= leftResult[2] && rightResult[2] >= crossResult[2])
            return rightResult;
        return crossResult;
    }

    public static void main(String[] args) {
        int size = 10;
        int [] array = new int[size];
        Random random = new Random();
        for(int i=0; i<size; i++) array[i] = random.nextInt(40) - 20;
        for(int num: array) System.out.print(num + " ");
        System.out.println();
        int [] maxSum = maxSubarray(array, 0, size-1);
        for(int num: maxSum) System.out.print(num + " ");
        

    }
}